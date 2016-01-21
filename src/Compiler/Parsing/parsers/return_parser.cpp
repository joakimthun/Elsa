#include "return_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ReturnParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Return);

			auto ret_exp = std::make_unique<ReturnExpression>();

			if (parser->current_token()->get_type() == TokenType::Semicolon)
			{
				ret_exp->set_type(new ElsaType(ObjectType::Void));

			}
			else
			{
				ret_exp->set_expression(parser->parse_expression());

				if (!parser->type_checker().valid_return_expression(ret_exp->get_expression()))
					throw ParsingException(L"Invalid return expression", parser->current_token());

				ret_exp->set_type(parser->type_checker().get_expression_type(ret_exp->get_expression()));
			}

			if(parser->current_token()->get_type() == TokenType::Semicolon)
				parser->consume(TokenType::Semicolon);

			return std::move(ret_exp);
		}

	}
}
