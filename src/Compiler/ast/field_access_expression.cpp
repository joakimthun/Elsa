#include "field_access_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		FieldAccessExpression::FieldAccessExpression(const std::wstring& name)
			:
			name_(name)
		{}

		void FieldAccessExpression::set_type(ElsaType * type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		const std::wstring& FieldAccessExpression::get_name() const
		{
			return name_;
		}

		const ElsaType* FieldAccessExpression::get_type() const
		{
			return type_.get();
		}

		void FieldAccessExpression::accept(ExpressionVisitor* visitor)
		{
			//visitor->visit(this);
		}
	}
}
