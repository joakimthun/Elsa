#pragma once

#include <memory>

#include "expression.h"
#include "../../lexing/token.h"

namespace elsa {
	namespace compiler {

		class BinaryOperatorExpression : public Expression
		{
		public:
			void set_operator(TokenType op);
			void set_left(Expression* left);
			void set_right(Expression* right);

			TokenType get_operator() const;
			Expression* get_left() const;
			Expression* get_right() const;

		private:
			TokenType operator_;
			std::unique_ptr<Expression> left_;
			std::unique_ptr<Expression> right_;
		};
	}
}