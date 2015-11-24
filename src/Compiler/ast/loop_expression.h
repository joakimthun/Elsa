#pragma once

#include <memory>
#include <vector>
#include <utility>

#include "expression.h"
#include "variable_declaration_expression.h"
#include "../token.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		enum class LoopType 
		{
			For,
			While
		};

		class LoopExpression : public Expression
		{
		public:
			void set_variable_expression(std::unique_ptr<Expression> expression);
			void set_condition(std::unique_ptr<Expression> expression);
			void set_post_expression(std::unique_ptr<Expression> expression);
			void add_to_body(std::unique_ptr<Expression> expression);

			Expression* get_variable_expression();
			Expression* get_condition();
			Expression* get_post_expression();
			const std::vector<std::unique_ptr<Expression>>& get_body() const;

			void set_type(LoopType type);
			LoopType get_type();
			

			void accept(ExpressionVisitor* visitor) override;

		private:
			LoopType type_;
			std::unique_ptr<Expression> variable_expression_;
			std::unique_ptr<Expression> condition_;
			std::unique_ptr<Expression> post_expression_;
			std::vector<std::unique_ptr<Expression>> body_;
		};
	}
}