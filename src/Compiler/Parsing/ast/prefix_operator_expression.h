#pragma once

#include <memory>

#include "expression.h"
#include "../../lexing/token.h"

namespace elsa {
	namespace compiler {

		class PrefixOperatorExpression : public Expression
		{
		public:
			PrefixOperatorExpression(TokenType op, Expression* right);

		private:
			TokenType op_;
			std::unique_ptr<Expression> right_;
		};

	}
}
