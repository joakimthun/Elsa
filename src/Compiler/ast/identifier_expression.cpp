#include "identifier_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		IdentifierExpression::IdentifierExpression(const std::wstring& name)
			:
			name_(name)
		{}

		void IdentifierExpression::set_type(ElsaType * type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		const std::wstring& IdentifierExpression::get_name() const
		{
			return name_;
		}

		ElsaType* IdentifierExpression::get_type()
		{
			return type_.get();
		}

		void IdentifierExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}
