#include "struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		void StructDeclarationExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void StructDeclarationExpression::add_field_expression(FieldExpression* expression)
		{
			fields_.push_back(std::unique_ptr<FieldExpression>(expression));
		}

		const std::wstring& StructDeclarationExpression::get_name() const
		{
			return name_;
		}

		const std::vector<std::unique_ptr<FieldExpression>>& StructDeclarationExpression::get_fields() const
		{
			return fields_;
		}

		void StructDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			throw ElsaException("No visit method defined for StructDeclarationExpression");
		}
	}
}

