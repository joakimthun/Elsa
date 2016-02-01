#include "create_struct_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> CreateStructParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::New);

			if (is_array_initializer_list(parser))
				return parse_array_initializer_list(parser);

			if (is_array(parser))
				return parse_array(parser);

			auto identifier = parser->current_token()->get_value();

			parser->consume(TokenType::Identifier);

			auto cse = std::make_unique<CreateStructExpression>(identifier, parser->type_checker().get_struct_type(identifier));

			if (parser->current_token()->get_type() == TokenType::LBracket)
				return parse_struct_initializer_list(std::move(cse), parser);

			return std::move(cse);
		}

		std::unique_ptr<Expression> CreateStructParser::parse_struct_initializer_list(std::unique_ptr<CreateStructExpression> cse, ElsaParser* parser)
		{
			auto sile = std::make_unique<StructInitializerListExpression>();

			sile->set_create_struct_expression(std::move(cse));

			parser->consume(TokenType::LBracket);

			if (parser->current_token()->get_type() != TokenType::RBracket)
			{
				auto sde = sile->get_create_struct_expression()->get_type()->get_struct_declaration_expression();

				while (parser->current_token()->get_type() != TokenType::RBracket)
				{
					auto field_name = parser->current_token()->get_value();
					parser->consume(TokenType::Identifier);
					parser->consume(TokenType::Colon);

					auto value_expression = parser->parse_expression();

					auto match = false;
					for (const auto& field : sde->get_fields())
					{
						if (field->get_name() == field_name)
						{
							auto value_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(value_expression.get()));
							if (!parser->type_checker().is_same_type(field->get_type(), value_type.get()))
								throw ParsingException(L"Cannot convert type '" + field->get_type()->get_name() + L"' to '" + value_type->get_name() + L"'", parser->current_token());

							sile->add_value_expression(std::make_unique<FieldInitializerExpression>(std::move(value_expression), field->get_index()));
							match = true;
							break;
						}
					}

					if(!match)
						throw ParsingException(L"'" + sde->get_name() + L"' does not contain a definition for '" + field_name + L"'", parser->current_token());

					if(parser->current_token()->get_type() == TokenType::Comma)
						parser->consume(TokenType::Comma);
				}
			}

			parser->consume(TokenType::RBracket);

			if (parser->current_token()->get_type() == TokenType::Semicolon)
				parser->consume(TokenType::Semicolon);

			return std::move(sile);
		}

		std::unique_ptr<Expression> CreateStructParser::parse_array(ElsaParser* parser)
		{
			auto arr_exp = std::make_unique<ArrayDeclarationExpression>();
			
			auto type = std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));

			auto array_struct = parser->struct_table().get(L"Array")->get_expression();
			auto array_type = array_struct->create_generic(std::move(type), parser);

			arr_exp->set_type(new ElsaType(array_type));

			parser->consume(TokenType::LSBracket);

			if (parser->current_token()->get_type() != TokenType::RSBracket)
			{
				auto size_expression = parser->parse_expression();
				auto size_expression_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(size_expression.get()));

				if (size_expression_type->get_type() != ObjectType::Int)
					throw ParsingException(L"Only integers are supported when specifying an array size", parser->current_token());

				arr_exp->set_size_expression(std::move(size_expression));
			}

			parser->consume(TokenType::RSBracket);

			return std::move(arr_exp);
		}

		std::unique_ptr<Expression> CreateStructParser::parse_array_initializer_list(ElsaParser* parser)
		{
			auto exp = std::make_unique<ArrayInitializerListExpression>();

			parser->consume(TokenType::LSBracket);

			while (parser->current_token()->get_type() != TokenType::RSBracket)
			{
				exp->add_value(parser->parse_expression());
				
				if (parser->current_token()->get_type() != TokenType::RSBracket)
					parser->consume(TokenType::Comma);
			}

			parser->consume(TokenType::RSBracket);

			if (exp->get_values().size() == 0)
				throw ParsingException(L"Array initializer lists must contain at least one value", parser->current_token());

			auto type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(exp->get_values()[0].get()));
			for (const auto& value : exp->get_values())
			{
				auto value_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(value.get()));
				if (!parser->type_checker().is_same_type(type.get(), value_type.get()))
					throw ParsingException(L"All expressions in the initializer list must be of the same type", parser->current_token());

				type.reset(value_type.release());
			}

			auto array_struct = parser->struct_table().get(L"Array")->get_expression();
			auto array_type = array_struct->create_generic(std::move(type), parser);

			exp->set_type(new ElsaType(array_type));

			return std::move(exp);
		}

		bool CreateStructParser::is_array(ElsaParser* parser)
		{
			return
				(parser->current_token()->get_type() == TokenType::Identifier ||
				parser->current_token()->get_type() == TokenType::Int ||
				parser->current_token()->get_type() == TokenType::Float ||
				parser->current_token()->get_type() == TokenType::Bool ||
				parser->current_token()->get_type() == TokenType::Char)
				&& parser->peek_token()->get_type() == TokenType::LSBracket;
		}

		bool CreateStructParser::is_array_initializer_list(ElsaParser* parser)
		{
			return	parser->current_token()->get_type() == TokenType::LSBracket;
		}

	}
}

