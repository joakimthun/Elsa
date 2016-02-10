#include "array_initializer_list_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ArrayInitializerListExpression::set_type(ElsaType* type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		const ElsaType* ArrayInitializerListExpression::get_type() const
		{
			return type_.get();
		}

		void ArrayInitializerListExpression::add_value(std::unique_ptr<Expression> exp)
		{
			values_.push_back(std::move(exp));
		}

		const std::vector<std::unique_ptr<Expression>>& ArrayInitializerListExpression::get_values() const
		{
			return values_;
		}

		void ArrayInitializerListExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}
