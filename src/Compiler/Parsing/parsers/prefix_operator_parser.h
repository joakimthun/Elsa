#pragma once

#include "parser.h"
#include "../nodes/prefix_operator_expression.h"

namespace elsa {
	namespace compiler {

		class PrefixOperatorParser : public Parser
		{
		public:
			Expression* parse(ElsaParser* parser, Token* token) override;
		};

	}
}
