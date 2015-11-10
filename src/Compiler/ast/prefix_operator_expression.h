#pragma once

#include <memory>

#include "expression.h"
#include "../token.h"

namespace elsa {
	namespace compiler {

		class PrefixOperatorExpression : public Expression
		{
		public:
			PrefixOperatorExpression(TokenType op, std::unique_ptr<Expression> right);

			TokenType get_operator() const;
			Expression* get_right() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			TokenType op_;
			std::unique_ptr<Expression> right_;
		};

	}
}
