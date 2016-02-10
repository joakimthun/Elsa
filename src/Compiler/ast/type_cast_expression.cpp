#include "type_cast_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		void TypeCastExpression::set_dest_type(ElsaType* type)
		{
			dest_type_ = std::unique_ptr<ElsaType>(type);
		}

		ElsaType* TypeCastExpression::get_dest_type()
		{
			return dest_type_.get();
		}

		void TypeCastExpression::set_expression(std::unique_ptr<Expression> expression)
		{
			expression_ = std::move(expression);
		}
			
		Expression* TypeCastExpression::get_expression()
		{
			return expression_.get();
		}

		void TypeCastExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}
