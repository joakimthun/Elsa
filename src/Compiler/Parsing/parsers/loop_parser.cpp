#include "loop_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> LoopParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Loop);
			parser->consume(TokenType::LParen);

			auto loop_exp = std::make_unique<LoopExpression>();

			loop_exp->set_variable_expression(parser->parse_expression());

			if (dynamic_cast<VariableDeclarationExpression*>(loop_exp->get_variable_expression()) == nullptr)
				throw ParsingException("The first part of a for loop must be a variable declaration");

			loop_exp->set_condition(parser->parse_expression());

			auto condition_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(loop_exp->get_condition()));
			if(condition_type->get_type() != ObjectType::Bool)
				throw ParsingException("The second part of a for loop must be a boolean expression");

			parser->consume(TokenType::Semicolon);
			loop_exp->set_post_expression(parser->parse_expression());

			parser->consume(TokenType::RParen);
			parser->consume(TokenType::LBracket);

			while (parser->current_token()->get_type() != TokenType::RBracket)
			{
				loop_exp->add_to_body(parser->parse_expression());
			}

			parser->consume(TokenType::RBracket);


			return std::move(loop_exp);
		}

	}
}
