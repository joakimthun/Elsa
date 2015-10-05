#pragma once

#include "../nodes/expression.h"
#include "../../lexing/token.h"
#include "../parser.h"

namespace elsa {
	namespace compiler {

		class Parser;

		class PrefixParselet
		{
		public:
			virtual ~PrefixParselet() {};
			virtual Expression* parse(Parser* parser, Token* token) = 0;
		};

	}
}


