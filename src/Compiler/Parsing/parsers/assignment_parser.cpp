#include "assignment_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> AssignmentParser::parse(ElsaParser* parser, std::unique_ptr<Expression> left)
		{
			parser->consume(TokenType::Equals);

			auto exp = std::make_unique<AssignmentExpression>();

			exp->set_left(std::move(left));

			assert_valid_assignment(parser, exp->get_left());

			exp->set_right(std::move(parser->parse_expression(precedence())));

			auto left_type = std::unique_ptr<ElsaType>(parser->type_checker().get_expression_type(exp->get_left()));

			if(!parser->type_checker().valid_assignment(exp.get()))
				throw ParsingException(L"Invalid assignment. The right hand side of the expression must be of type '" + left_type->get_name() + L"'", parser->current_token());

			if(parser->current_token()->get_type() == TokenType::Semicolon)
				parser->consume(TokenType::Semicolon);

			return std::move(exp);
		}

		int AssignmentParser::precedence()
		{
			return Precedence::Assignment;
		}

		void AssignmentParser::assert_valid_assignment(ElsaParser* parser, Expression* left)
		{
			if (!parser->type_checker().is_assignable(left))
				throw ParsingException(L"Values can only be assigned to local variables", parser->current_token());
		}

	}
}
