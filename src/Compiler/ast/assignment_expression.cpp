#include "assignment_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {
		
		void AssignmentExpression::set_left(std::unique_ptr<Expression> left)
		{
			left_ = std::move(left);
		}

		void AssignmentExpression::set_right(std::unique_ptr<Expression> right)
		{
			right_ = std::move(right);
		}

		Expression* AssignmentExpression::get_left() const
		{
			return left_.get();
		}

		Expression* AssignmentExpression::get_right() const
		{
			return right_.get();
		}

		void AssignmentExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

