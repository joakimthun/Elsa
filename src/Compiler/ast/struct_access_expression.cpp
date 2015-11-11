#include "struct_access_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructAccessExpression::add_expression(std::unique_ptr<IdentifierExpression> expression)
		{
			expressions_.push_back(std::move(expression));
		}

		const std::vector<std::unique_ptr<IdentifierExpression>>& StructAccessExpression::get_expressions() const
		{
			return expressions_;
		}

		void StructAccessExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}
