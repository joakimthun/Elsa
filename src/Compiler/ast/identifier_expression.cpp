#include "identifier_expression.h"

namespace elsa {
	namespace compiler {

		IdentifierExpression::IdentifierExpression(const std::wstring& name)
			:
			name_(name)
		{}

		const std::wstring& IdentifierExpression::get_name() const
		{
			return name_;
		}

		void IdentifierExpression::accept(ExpressionVisitor* visitor)
		{
			//visitor->visit(this);
			throw ElsaException("No visit method defined for IdentifierExpression");
		}
	}
}
