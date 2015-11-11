#include "field_access_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void FieldAccessExpression::add_expression(std::unique_ptr<IdentifierExpression> expression)
		{
			expressions_.push_back(std::move(expression));
		}

		const std::vector<std::unique_ptr<IdentifierExpression>>& FieldAccessExpression::get_expressions() const
		{
			return expressions_;
		}

		void FieldAccessExpression::accept(ExpressionVisitor* visitor)
		{
			throw ParsingException("Undefined visitor FieldAccessExpression");
		}

	}
}
