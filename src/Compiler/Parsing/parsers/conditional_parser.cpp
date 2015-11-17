#include "conditional_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ConditionalParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::If);
			parser->consume(TokenType::LParen);

			auto cond_exp = std::make_unique<ConditionalExpression>();
			cond_exp->set_condition(parser->parse_expression());

			parser->consume(TokenType::RParen);
			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				cond_exp->add_to_if_body(parser->parse_expression());
			}

			parser->consume(TokenType::RBracket);

			if (parser->current_token()->get_type() == TokenType::Else)
			{
				parser->consume(TokenType::Else);
				parser->consume(TokenType::LBracket);

				while (parser->current_token()->get_type() != TokenType::RBracket)
				{
					cond_exp->add_to_else_body(parser->parse_expression());
				}

				parser->consume(TokenType::RBracket);
			}

			return std::move(cond_exp);
		}

	}
}
