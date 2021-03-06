#include "loop_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> LoopParser::parse(ElsaParser* parser)
		{
			LoopType loop_type;

			if (parser->current_token()->get_type() == TokenType::For)
			{
				loop_type = LoopType::For;
				parser->consume(TokenType::For);
			}
			else
			{
				loop_type = LoopType::While;
				parser->consume(TokenType::While);
			}

			parser->consume(TokenType::LParen);

			auto loop_exp = std::make_unique<LoopExpression>(parser->current_scope());
			parser->push_new_scope(loop_exp.get());

			auto first_exp = parser->parse_expression();
			auto first_exp_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(first_exp.get()));
			if (loop_type == LoopType::While)
			{
				loop_exp->set_condition(std::move(first_exp));
				loop_exp->set_type(LoopType::While);
			}
			else
			{
				if (dynamic_cast<VariableDeclarationExpression*>(first_exp.get()) == nullptr)
					throw ParsingException(L"The first part of a for loop must be a variable declaration", parser->current_token());

				loop_exp->set_variable_expression(std::move(first_exp));
				loop_exp->set_condition(parser->parse_expression());

				auto condition_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(loop_exp->get_condition()));
				if (condition_type->get_type() != ObjectType::Bool)
					throw ParsingException(L"The second part of a for loop must be a boolean expression", parser->current_token());

				if(parser->current_token()->get_type() == TokenType::Semicolon)
					parser->consume(TokenType::Semicolon);

				loop_exp->set_post_expression(parser->parse_expression());

				loop_exp->set_type(LoopType::For);
			}

			parser->consume(TokenType::RParen);
			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				loop_exp->add_to_body(parser->parse_expression());
			}

			parser->consume(TokenType::RBracket);

			parser->pop_current_scope();


			return std::move(loop_exp);
		}

	}
}
