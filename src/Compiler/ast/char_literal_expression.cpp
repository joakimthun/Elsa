#include "char_literal_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

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

		void CharLiteralExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

