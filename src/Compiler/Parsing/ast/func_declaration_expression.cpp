#include "func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		void FuncDeclarationExpression::add_expression(Expression* expression)
		{
			body_.push_back(std::unique_ptr<Expression>(expression));
		}

		void FuncDeclarationExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void FuncDeclarationExpression::set_return_type(ElsaType* return_type)
		{
			return_type_ = std::unique_ptr<ElsaType>(return_type);
		}

		const std::wstring& FuncDeclarationExpression::get_name() const
		{
			return name_;
		}

		const ElsaType* FuncDeclarationExpression::get_return_type() const
		{
			return return_type_.get();
		}

		const std::vector<std::unique_ptr<Expression>>& FuncDeclarationExpression::get_body() const
		{
			return body_;
		}
	}
}
