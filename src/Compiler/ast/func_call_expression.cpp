#include "func_call_expression.h"

namespace elsa {
	namespace compiler {

		void FuncCallExpression::add_args_expression(std::unique_ptr<Expression> expression)
		{
			args_.push_back(std::move(expression));
		}

		void FuncCallExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		const std::wstring& FuncCallExpression::get_name() const
		{
			return name_;
		}

		const std::vector<std::unique_ptr<Expression>>& FuncCallExpression::get_args() const
		{
			return args_;
		}

		void FuncCallExpression::accept(ExpressionVisitor* visitor)
		{
			//throw;
		}
	}
}




