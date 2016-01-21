#include "string_literal_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

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

		void StringLiteralExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

