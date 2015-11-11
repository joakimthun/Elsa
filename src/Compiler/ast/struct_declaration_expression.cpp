#include "struct_declaration_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructDeclarationExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void StructDeclarationExpression::add_field_expression(std::unique_ptr<FieldExpression> expression)
		{
			fields_.push_back(std::move(expression));
			fields_.back()->set_index(fields_.size() - 1);
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
			visitor->visit(this);
		}
	}
}

