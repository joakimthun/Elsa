#include "integer_literal_expression.h"

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

	}
}

