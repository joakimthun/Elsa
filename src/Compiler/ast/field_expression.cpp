#include "field_expression.h"

namespace elsa {
	namespace compiler {

		void FieldExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void FieldExpression::set_type(ElsaType* type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		const std::wstring& FieldExpression::get_name() const
		{
			return name_;
		}

		const ElsaType* FieldExpression::get_type() const
		{
			return type_.get();
		}

		void FieldExpression::accept(ExpressionVisitor* visitor)
		{
			//visitor->visit(this);
			throw ElsaException("No visit method defined for FieldExpression");
		}
	}
}
