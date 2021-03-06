#include "float_literal_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		FloatLiteralExpression::FloatLiteralExpression(float value)
			:
			value_(value)
		{}

		float FloatLiteralExpression::get_value() const
		{
			return value_;
		}

		void FloatLiteralExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

