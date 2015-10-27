#include "integer_literal_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		IntegerLiteralExpression::IntegerLiteralExpression(int value)
			:
			value_(value)
		{}

		int IntegerLiteralExpression::get_value() const
		{
			return value_;
		}

		void IntegerLiteralExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

