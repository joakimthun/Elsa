#include "variable_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> VariableDeclarationParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Var);

			auto name = parser->current_token()->get_value();

			if (parser->current_scope()->has_local(name))
				throw ParsingException("A local variable with the same name has already been declared");

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::Equals);

			auto expression = std::unique_ptr<Expression>(parser->parse_expression());
			auto expression_type = parser->type_checker().get_expression_type(expression.get());

			auto struct_expression = dynamic_cast<CreateStructExpression*>(expression.get());
			auto array_expression = dynamic_cast<ArrayDeclarationExpression*>(expression.get());
			if (struct_expression != nullptr || array_expression != nullptr)
			{
				auto entry_name = struct_expression != nullptr ? struct_expression->get_struct_name() : L"Array";
				if (!parser->struct_table().has_entry(entry_name))
					throw ParsingException("No struct with that name is defined");

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

			return std::make_unique<VariableDeclarationExpression>(name, expression_type, std::move(expression));
		}

	}
}
