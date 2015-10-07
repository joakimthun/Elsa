#include "string_literal_expression.h"

namespace elsa {
	namespace compiler {

		StringLiteralExpression::StringLiteralExpression(const std::wstring& value)
			:
			value_(value)
		{}

		const std::wstring& StringLiteralExpression::get_value() const
		{
			return value_;
		}

	}
}

