#pragma once

#include <memory>
#include <vector>
#include <utility>

#include "expression.h"
#include "../token.h"
#include "../types/elsa_type.h"
#include "scoped_expression.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ConditionalExpression : public Expression
		{
		public:
			void set_condition(std::unique_ptr<Expression> expression);
			void add_to_if_body(std::unique_ptr<Expression> expression);
			void add_to_else_body(std::unique_ptr<Expression> expression);

			Expression* get_condition();
			const std::vector<std::unique_ptr<Expression>>& get_if_body() const;
			const std::vector<std::unique_ptr<Expression>>& get_else_body() const;
			bool has_else_body() const;

			void set_if_scope(std::unique_ptr<ScopedExpression> scope);
			void set_else_scope(std::unique_ptr<ScopedExpression> scope);
			ScopedExpression* get_if_scope();
			ScopedExpression* get_else_scope();

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<Expression> condition_;
			std::vector<std::unique_ptr<Expression>> if_body_;
			std::vector<std::unique_ptr<Expression>> else_body_;
			std::unique_ptr<ScopedExpression> if_body_scope_;
			std::unique_ptr<ScopedExpression> else_body_scope_;
		};
	}
}
