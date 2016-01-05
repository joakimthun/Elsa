#include "create_struct_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> CreateStructParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::New);

			if (is_array(parser))
				return parse_array(parser);

			auto identifier = parser->current_token()->get_value();

			parser->consume(TokenType::Identifier);

			return std::make_unique<CreateStructExpression>(identifier, parser->type_checker().get_struct_type(identifier));
		}

		std::unique_ptr<Expression> CreateStructParser::parse_array(ElsaParser* parser)
		{
			auto arr_exp = std::make_unique<ArrayDeclarationExpression>();

			auto type = std::unique_ptr<ElsaType>(parser->type_checker().get_type_from_token(parser->current_token()));

			auto array_struct = parser->struct_table().get(L"Array")->get_expression();
			auto array_type = array_struct->create_generic(std::move(type), parser);

			arr_exp->set_type(new ElsaType(array_type));

			parser->consume();
			parser->consume(TokenType::LSBracket);
			parser->consume(TokenType::RSBracket);

			return std::move(arr_exp);
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

	}
}

