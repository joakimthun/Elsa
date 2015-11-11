#include "struct_access_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructAccessExpression::set_base(std::unique_ptr<IdentifierExpression> expression)
		{
			base_ = std::move(expression);
		}

		void StructAccessExpression::add_expression(std::unique_ptr<FieldAccessExpression> expression)
		{
			expressions_.push_back(std::move(expression));
		}

		IdentifierExpression* StructAccessExpression::get_base()
		{
			return base_.get();
		}

		const std::vector<std::unique_ptr<FieldAccessExpression>>& StructAccessExpression::get_expressions() const
		{
			return expressions_;
		}

		void StructAccessExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}
