#pragma once

#include <memory>

#include "infix_parser.h"
#include "../../ast/binary_operator_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"
#include "./../precedence.h"

namespace elsa {
	namespace compiler {

		class BinaryOperatorParser : public InfixParser
		{
		public:
			BinaryOperatorParser(Precedence precedence);

			Expression* parse(ElsaParser* parser, Expression* left) override;
			int precedence() override;

		private:
			Precedence precedence_;
		};

	}
}
