#include "enum_declaration_expression.h"

#include "../expression_visitor.h"

namespace elsa {
	namespace compiler {

		void EnumDeclarationExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void EnumDeclarationExpression::add_value(const std::wstring& name, int value)
		{
			members_.insert(std::pair<std::wstring, int>(name, value));
		}

		int EnumDeclarationExpression::get_value(const std::wstring& name) const
		{
			auto it = members_.find(name);
			if (it != members_.end())
			{
				return it->second;
			}

			throw ParsingException(L"The enum '" + name_ + L"' has no member with the name '" + name + L"'");
		}

		const ElsaType* EnumDeclarationExpression::get_type() const
		{
			return type_.get();
		}

		void EnumDeclarationExpression::set_type(ElsaType* type)
		{
			type_.reset(type);
		}

		const std::wstring& EnumDeclarationExpression::get_name() const
		{
			return name_;
		}

		void EnumDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

	}
}

