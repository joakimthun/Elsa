#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "expression.h"
#include "func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class FuncCallExpression : public Expression
		{
		public:
			void add_args_expression(std::unique_ptr<Expression> expression);

			void set_func_declaration_expression(const FuncDeclarationExpression* fde);

			const std::wstring& get_name() const;
			const std::vector<std::unique_ptr<Expression>>& get_args() const;
			const FuncDeclarationExpression* get_func_declaration_expression() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::vector<std::unique_ptr<Expression>> args_;
			const FuncDeclarationExpression* fde_;
		};
	}
}

