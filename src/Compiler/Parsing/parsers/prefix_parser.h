#pragma once

#include "../nodes/expression.h"
#include "../../lexing/token.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class ElsaParser;

		class PrefixParser
		{
		public:
			virtual ~PrefixParser() {};
			virtual Expression* parse(ElsaParser* parser, Token* token) = 0;
		};

	}
}


