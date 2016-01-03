#include "func_call_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void FuncCallExpression::add_args_expression(std::unique_ptr<Expression> expression)
		{
			args_.push_back(std::move(expression));
		}

		void FuncCallExpression::set_func_declaration_expression(const FuncDeclarationExpression* fde)
		{
			fde_ = fde;
		}

		const std::wstring& FuncCallExpression::get_name() const
		{
			return fde_->get_name();
		}

		const ElsaType* FuncCallExpression::get_type() const
		{
			return fde_->get_return_type();
		}

		const std::vector<std::unique_ptr<Expression>>& FuncCallExpression::get_args() const
		{
			return args_;
		}

		const FuncDeclarationExpression * FuncCallExpression::get_func_declaration_expression() const
		{
			return fde_;
		}

		void FuncCallExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}




