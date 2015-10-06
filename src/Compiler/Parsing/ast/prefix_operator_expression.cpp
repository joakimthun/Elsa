#include "prefix_operator_expression.h"

namespace elsa {
	namespace compiler {

			PrefixOperatorExpression::PrefixOperatorExpression(TokenType op, Expression* right)
				:
				op_(op),
				right_(right)
			{}

			TokenType PrefixOperatorExpression::get_operator() const
			{
				return op_;
			}

			Expression* PrefixOperatorExpression::get_right() const
			{
				return right_.get();
			}
	}
}
