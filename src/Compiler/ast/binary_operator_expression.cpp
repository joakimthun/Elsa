#include "binary_operator_expression.h"

namespace elsa {
	namespace compiler {

		void BinaryOperatorExpression::set_operator(TokenType op)
		{
			operator_ = op;
		}
		void BinaryOperatorExpression::set_left(Expression* left)
		{
			left_ = std::unique_ptr<Expression>(left);
		}

		void BinaryOperatorExpression::set_right(Expression* right)
		{
			right_ = std::unique_ptr<Expression>(right);
		}

		TokenType BinaryOperatorExpression::get_operator() const
		{
			return operator_;
		}

		Expression* BinaryOperatorExpression::get_left() const
		{
			return left_.get();
		}

		Expression* BinaryOperatorExpression::get_right() const
		{
			return right_.get();
		}

	}
}
