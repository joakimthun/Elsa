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

		void StructDeclarationExpression::add_member_function(std::unique_ptr<FuncDeclarationExpression> expression)
		{
			functions_.push_back(std::move(expression));
		}

		const FuncDeclarationExpression* StructDeclarationExpression::get_member_function(const std::wstring& name) const
		{
			for (const auto& f : functions_)
			{
				if (f->get_name() == name)
					return f.get();
			}

			throw ParsingException("Undefined member function");
		}

		const std::wstring& StructDeclarationExpression::get_name() const
		{
			return name_;
		}

		const std::vector<std::unique_ptr<FieldExpression>>& StructDeclarationExpression::get_fields() const
		{
			return fields_;
		}

		const std::vector<std::unique_ptr<FuncDeclarationExpression>>& StructDeclarationExpression::get_functions() const
		{
			return functions_;
		}

		void StructDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}

