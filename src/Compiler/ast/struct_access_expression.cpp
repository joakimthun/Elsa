#include "struct_access_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructAccessExpression::set_base(std::unique_ptr<IdentifierExpression> expression)
		{
			base_ = std::move(expression);
		}

		void StructAccessExpression::add_expression(TypedExpression* expression)
		{
			expressions_.push_back(std::unique_ptr<TypedExpression>(expression));
		}

		IdentifierExpression* StructAccessExpression::get_base()
		{
			return base_.get();
		}

		const std::vector<std::unique_ptr<TypedExpression>>& StructAccessExpression::get_expressions() const
		{
			return expressions_;
		}

		void StructAccessExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}
