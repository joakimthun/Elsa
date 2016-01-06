#include "variable_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> VariableDeclarationParser::parse(ElsaParser* parser)
		{
			std::unique_ptr<ElsaType> explicit_type;
			if (is_explicit(parser))
			{
				explicit_type = get_explicit_type(parser);
				parser->consume();
			}
			else
			{
				parser->consume(TokenType::Var);
			}

			auto name = parser->current_token()->get_value();

			if (parser->current_scope()->has_local(name))
				throw ParsingException(L"A local variable with the same name has already been declared", parser->current_token());

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::Equals);

			auto expression = std::unique_ptr<Expression>(parser->parse_expression());
			auto expression_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(expression.get()));

			if (explicit_type.get() != nullptr)
				assert_is_valid_declaration(explicit_type.get(), expression_type.get(), parser);

			auto struct_expression = dynamic_cast<CreateStructExpression*>(expression.get());
			auto array_expression = dynamic_cast<ArrayDeclarationExpression*>(expression.get());
			if (struct_expression != nullptr || array_expression != nullptr)
			{
				auto entry_name = struct_expression != nullptr ? struct_expression->get_struct_name() : array_expression->get_type()->get_name();
				if (!parser->struct_table().has_entry(entry_name))
					throw ParsingException(L"No struct with that name is defined", parser->current_token());

				// Struct
				auto si = parser->struct_table().get(entry_name);
				parser->current_scope()->add_local(name, *expression_type, si->get_expression());
			}
			else
			{
				// Other types
				parser->current_scope()->add_local(name, *expression_type);
			}

			if(parser->current_token()->get_type() == TokenType::Semicolon)
				parser->consume(TokenType::Semicolon);

			return std::make_unique<VariableDeclarationExpression>(name, expression_type.release(), std::move(expression));
		}

		bool VariableDeclarationParser::is_explicit(ElsaParser* parser)
		{
			auto current_token_type = parser->current_token()->get_type();
			return current_token_type == TokenType::Int || 
				current_token_type == TokenType::Float || 
				current_token_type == TokenType::Char || 
				current_token_type == TokenType::Bool ||
				current_token_type == TokenType::Identifier;
		}

		std::unique_ptr<ElsaType> VariableDeclarationParser::get_explicit_type(ElsaParser* parser)
		{
			return std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));
		}

		void VariableDeclarationParser::assert_is_valid_declaration(const ElsaType* expected, const ElsaType* actual, ElsaParser* parser)
		{
			if (expected->get_type() != actual->get_type())
				throw ParsingException(L"Both sides of a variable declaration expression must be of the same type.", parser->current_token());

			if (expected->get_type() == ObjectType::GCOPtr)
			{
				if(actual->get_type() != ObjectType::GCOPtr)
					throw ParsingException(L"Both sides of a variable declaration expression must be of the same type.", parser->current_token());
				else
				{
					if(expected->get_struct_declaration_expression()->get_name() != actual->get_struct_declaration_expression()->get_name())
						throw ParsingException(L"Both sides of a variable declaration expression must be of the same type.", parser->current_token());
				}
			}
		}

	}
}
