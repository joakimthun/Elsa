#include "binary_operator_parser.h"

namespace elsa {
	namespace compiler {

		BinaryOperatorParser::BinaryOperatorParser(Precedence precedence)
			:
			precedence_(precedence)
		{}

		std::unique_ptr<Expression> BinaryOperatorParser::parse(ElsaParser* parser, std::unique_ptr<Expression> left)
		{
			auto exp = std::make_unique<BinaryOperatorExpression>();
			exp->set_operator(parser->current_token()->get_type());

			// Consume the operator token
			parser->consume();

			exp->set_left(std::move(left));
			exp->set_right(std::move(parser->parse_expression(precedence())));

			exp->set_type(TypeChecker::get_expression_type(exp.get()));

			return std::move(exp);
		}

		int BinaryOperatorParser::precedence()
		{
			return static_cast<int>(precedence_);
		}

	}
}
