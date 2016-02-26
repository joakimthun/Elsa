#include "enum_value_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		EnumValueExpression::EnumValueExpression(int value)
			:
			value_(value)
		{}

		int EnumValueExpression::get_value() const
		{
			return value_;
		}

		const ElsaType* EnumValueExpression::get_type() const
		{
			return type_.get();
		}

		void EnumValueExpression::set_type(ElsaType* type)
		{
			type_.reset(type);
		}

		void EnumValueExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

