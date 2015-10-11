#pragma once

#include "../../token.h"

namespace elsa {
	namespace compiler {

		class Expression;
		class ElsaParser;

		class Parser
		{
		public:
			virtual ~Parser() {};
			virtual Expression* parse(ElsaParser* parser) = 0;
		};

	}
}


