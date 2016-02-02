#include "func_call_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		FuncCallExpression::FuncCallExpression(bool stack_invoke, const std::wstring& local_name)
			:
			stack_invoke_(stack_invoke),
			local_name_(local_name)
		{
		}

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

		ExpressionType FuncCallExpression::get_expression_type() const
		{
			return ExpressionType::FuncCall;
		}

		const std::vector<std::unique_ptr<Expression>>& FuncCallExpression::get_args() const
		{
			return args_;
		}

		const FuncDeclarationExpression * FuncCallExpression::get_func_declaration_expression() const
		{
			return fde_;
		}

		bool FuncCallExpression::stack_invoke() const
		{
			return stack_invoke_;
		}

		const std::wstring & FuncCallExpression::local_name() const
		{
			return local_name_;
		}

		void FuncCallExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}




