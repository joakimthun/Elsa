#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "expression.h"
#include "typed_expression.h"
#include "func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class FuncCallExpression : public Expression, public TypedExpression
		{
		public:
			FuncCallExpression(bool stack_invoke, const std::wstring& local_name);

			void add_args_expression(std::unique_ptr<Expression> expression);

			void set_func_declaration_expression(const FuncDeclarationExpression* fde);

			const std::wstring& get_name() const override;
			const ElsaType* get_type() const override;
			ExpressionType get_expression_type() const override;

			const std::vector<std::unique_ptr<Expression>>& get_args() const;
			const FuncDeclarationExpression* get_func_declaration_expression() const;

			bool stack_invoke() const;
			const std::wstring& local_name() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::vector<std::unique_ptr<Expression>> args_;
			const FuncDeclarationExpression* fde_;
			bool stack_invoke_;
			std::wstring local_name_;
		};
	}
}

