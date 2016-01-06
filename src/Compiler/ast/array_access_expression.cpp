#include "array_access_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ArrayAccessExpression::set_identifier_expression(std::unique_ptr<IdentifierExpression> identifier_expression)
		{
			identifier_expression_ = std::move(identifier_expression);
		}

		void ArrayAccessExpression::set_index_expression(std::unique_ptr<Expression> expression)
		{
			index_expression_ = std::move(expression);
		}

		IdentifierExpression* ArrayAccessExpression::get_identifier_expression() const
		{
			return identifier_expression_.get();
		}

		Expression* ArrayAccessExpression::get_index_expression() const
		{
			return index_expression_.get();
		}


		void ArrayAccessExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}
