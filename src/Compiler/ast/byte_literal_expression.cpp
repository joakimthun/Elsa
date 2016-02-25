#include "byte_literal_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		ByteLiteralExpression::ByteLiteralExpression(uint8_t value)
			:
			value_(value)
		{}

		uint8_t ByteLiteralExpression::get_value() const
		{
			return value_;
		}

		void ByteLiteralExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

