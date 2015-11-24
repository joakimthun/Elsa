#pragma once

#include <memory>

#include "expression.h"
#include "../token.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class PostfixOperatorExpression : public Expression
		{
		public:
			void set_operator(TokenType op);
			void set_expression(std::unique_ptr<Expression> expression);
			void set_type(ElsaType* type);

			TokenType get_operator() const;
			Expression* get_expression() const;
			ElsaType* get_type() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			TokenType operator_;
			std::unique_ptr<ElsaType> type_;
			std::unique_ptr<Expression> expression_;
		};
	}
}