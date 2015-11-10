#include "elsa_invoke_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ElsaInvokeParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Elsa);
			parser->consume(TokenType::Dot);

			auto elsa_invoke_exp = std::make_unique<ElsaInvokeExpression>(parser->current_token()->get_value());

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::LParen);

			while (parser->current_token()->get_type() != TokenType::RParen)
			{
				elsa_invoke_exp->add_args_expression(parser->parse_expression());

				if (parser->current_token()->get_type() != TokenType::RParen)
					parser->consume(TokenType::Comma);
			}

			parser->consume(TokenType::RParen);
			parser->consume(TokenType::Semicolon);

			return std::move(elsa_invoke_exp);
		}

	}
}

