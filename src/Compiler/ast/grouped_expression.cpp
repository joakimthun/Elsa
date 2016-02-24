#include "grouped_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		const ElsaType* GroupedExpression::get_type() const
		{
			return type_.get();
		}

		void GroupedExpression::set_type(ElsaType* type)
		{
			type_.reset(type);
		}

		Expression * GroupedExpression::get_expression()
		{
			return expression_.get();
		}

		void GroupedExpression::set_expression(std::unique_ptr<Expression> exp)
		{
			expression_ = std::move(exp);
		}
		
		void GroupedExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}
