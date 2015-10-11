#include "char_literal_expression.h"

namespace elsa {
	namespace compiler {

		CharLiteralExpression::CharLiteralExpression(wchar_t value)
			:
			value_(value)
		{}

		wchar_t CharLiteralExpression::get_value() const
		{
			return value_;
		}

	}
}

