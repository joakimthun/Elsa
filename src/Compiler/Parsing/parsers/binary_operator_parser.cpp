#include "binary_operator_parser.h"

namespace elsa {
	namespace compiler {
		BinaryOperatorParser::BinaryOperatorParser(Precedence precedence)
			:
			precedence_(precedence)
		{}

		Expression* BinaryOperatorParser::parse(ElsaParser* parser, Expression* left)
		{
			auto exp = std::make_unique<BinaryOperatorExpression>();
			exp->set_operator(parser->current_token()->get_type());

			// Consume the operator token
			parser->consume();

			exp->set_left(left);
			exp->set_right(parser->parse_expression(precedence()));

			return exp.release();
		}

		int BinaryOperatorParser::precedence()
		{
			return static_cast<int>(precedence_);
		}

	}
}
