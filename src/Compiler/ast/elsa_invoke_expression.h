#pragma once

#include <vector>
#include <memory>
#include <string>

#include "expression.h"
#include "argument_expression.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ElsaInvokeExpression : public Expression
		{
		public:
			ElsaInvokeExpression(const std::wstring& function_name);

			const std::wstring& get_function_name() const;

			void add_args_expression(Expression* expression);
			const std::vector<std::unique_ptr<Expression>>& get_args() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring function_name_;
			std::vector<std::unique_ptr<Expression>> args_;
		};
	}
}
