#include "elsa_invoke_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		ElsaInvokeExpression::ElsaInvokeExpression(const std::wstring& function_name)
			:
			function_name_(function_name)
		{}

		const std::wstring& ElsaInvokeExpression::get_function_name() const
		{
			return function_name_;
		}

		void ElsaInvokeExpression::add_args_expression(std::unique_ptr<Expression> expression)
		{
			args_.push_back(std::move(expression));
		}

		const std::vector<std::unique_ptr<Expression>>& ElsaInvokeExpression::get_args() const
		{
			return args_;
		}

		void ElsaInvokeExpression::accept(ExpressionVisitor* visitor)
		{
			//visitor->visit(this);
		}
	}
}


