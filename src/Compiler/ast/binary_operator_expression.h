#pragma once

#include <memory>

#include "expression.h"
#include "../token.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class BinaryOperatorExpression : public Expression
		{
		public:
			void set_operator(TokenType op);
			void set_left(Expression* left);
			void set_right(Expression* right);
			void set_type(ElsaType* type);

			TokenType get_operator() const;
			Expression* get_left() const;
			Expression* get_right() const;
			ElsaType* get_type() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			TokenType operator_;
			std::unique_ptr<ElsaType> type_;
			std::unique_ptr<Expression> left_;
			std::unique_ptr<Expression> right_;
		};
	}
}