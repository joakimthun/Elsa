#include "prefix_operator_expression.h"

namespace elsa {
	namespace compiler {

		PrefixOperatorExpression::PrefixOperatorExpression(TokenType op, Expression* right)
			:
			op(op),
			right(std::unique_ptr<Expression>(right))
		{}

	}
}
