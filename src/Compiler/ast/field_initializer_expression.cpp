#include "field_initializer_expression.h"

namespace elsa {
	namespace compiler {

		FieldInitializerExpression::FieldInitializerExpression(std::unique_ptr<Expression> exp, std::size_t index)
			:
			value_(std::move(exp)),
			index_(index)
		{
		}

		void FieldInitializerExpression::add_value(std::unique_ptr<Expression> exp)
		{
			value_ = std::move(exp);
		}

		Expression * FieldInitializerExpression::get_value()
		{
			return value_.get();
		}

		void FieldInitializerExpression::set_index(std::size_t index)
		{
			index_ = index;
		}

		std::size_t FieldInitializerExpression::get_index() const
		{
			return index_;
		}

		void FieldInitializerExpression::accept(ExpressionVisitor * visitor)
		{
		}

	}
}
