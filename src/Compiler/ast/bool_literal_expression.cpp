#include "bool_literal_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		BoolLiteralExpression::BoolLiteralExpression(bool value)
			:
			value_(value)
		{}

		bool BoolLiteralExpression::get_value() const
		{
			return value_;
		}

		void BoolLiteralExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

