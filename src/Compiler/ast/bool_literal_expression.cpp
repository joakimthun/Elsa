#include "bool_literal_expression.h"

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
			//visitor->visit(this);
			throw ElsaException("No visit method defined for BoolLiteralExpression");
		}

	}
}

