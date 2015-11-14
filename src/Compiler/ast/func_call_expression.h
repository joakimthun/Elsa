#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "expression.h"

namespace elsa {
	namespace compiler {

		class FuncCallExpression : public Expression
		{
		public:
			void add_args_expression(std::unique_ptr<Expression> expression);

			void set_name(const std::wstring& name);

			const std::wstring& get_name() const;
			const std::vector<std::unique_ptr<Expression>>& get_args() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::vector<std::unique_ptr<Expression>> args_;
		};
	}
}

