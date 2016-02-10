#include "return_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		Expression* ReturnExpression::get_expression() const
		{
			return expression_.get();
		}

		ElsaType* ReturnExpression::get_type() const
		{
			return type_.get();
		}

		void ReturnExpression::set_expression(std::unique_ptr<Expression> expression)
		{
			expression_ = std::move(expression);
		}

		void ReturnExpression::set_type(ElsaType* type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		void ReturnExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}
