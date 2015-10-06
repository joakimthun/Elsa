#pragma once

#include "../../lexing/token.h"

namespace elsa {
	namespace compiler {

		class Expression;
		class ElsaParser;

		class Parser
		{
		public:
			virtual ~Parser() {};
			virtual Expression* parse(ElsaParser* parser, Token* token) = 0;
		};

	}
}


