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

			cond_exp->set_if_scope(std::make_unique<ScopedExpression>(parser->current_scope()));
			parser->push_new_scope(cond_exp->get_if_scope());
			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				cond_exp->add_to_if_body(parser->parse_expression());
			}

			parser->pop_current_scope();

			parser->consume(TokenType::RBracket);

			if (parser->current_token()->get_type() == TokenType::Else)
			{
				cond_exp->set_else_scope(std::make_unique<ScopedExpression>(parser->current_scope()));
				parser->push_new_scope(cond_exp->get_else_scope());

				parser->consume(TokenType::Else);
				parser->consume(TokenType::LBracket);

				while (parser->current_token()->get_type() != TokenType::RBracket)
				{
					cond_exp->add_to_else_body(parser->parse_expression());
				}

				parser->pop_current_scope();

				parser->consume(TokenType::RBracket);
			}

			return std::move(cond_exp);
		}

	}
}
