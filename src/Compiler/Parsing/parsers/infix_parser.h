#pragma once

#include "../../token.h"

namespace elsa {
	namespace compiler {

		class Expression;
		class ElsaParser;

		class InfixParser
		{
		public:
			virtual ~InfixParser() {};
			virtual Expression* parse(ElsaParser* parser, Expression* left) = 0;
			virtual int precedence() = 0;
		};

	}
}



