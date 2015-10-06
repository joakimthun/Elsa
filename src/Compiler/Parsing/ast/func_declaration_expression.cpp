#include "func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		FuncDeclarationExpression::FuncDeclarationExpression(const std::wstring& name)
			:
			name_(name)
		{}

		void FuncDeclarationExpression::add_expression(Expression* expression)
		{
			body_.push_back(std::unique_ptr<Expression>(expression));
		}
	}
}
