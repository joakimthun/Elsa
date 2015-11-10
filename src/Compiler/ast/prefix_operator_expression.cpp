#include "prefix_operator_expression.h"

namespace elsa {
	namespace compiler {

		PrefixOperatorExpression::PrefixOperatorExpression(TokenType op, std::unique_ptr<Expression> right)
			:
			op_(op),
			right_(std::move(right))
		{}

		TokenType PrefixOperatorExpression::get_operator() const
		{
			return op_;
		}

		Expression* PrefixOperatorExpression::get_right() const
		{
			return right_.get();
		}

		void PrefixOperatorExpression::accept(ExpressionVisitor* visitor)
		{
			//visitor->visit(this);
			throw ElsaException("No visit method defined for PrefixOperatorExpression");
		}
	}
}
