#pragma once

#include <memory>

#include "expression.h"
#include "../../lexing/token.h"

namespace elsa {
	namespace compiler {

		struct PrefixOperatorExpression : public Expression
		{
			PrefixOperatorExpression(TokenType op, Expression* right);

			TokenType op;
			std::unique_ptr<Expression> right;
		};

	}
}
