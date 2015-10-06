#pragma once

#include "prefix_parser.h"
#include "../nodes/prefix_operator_expression.h"

namespace elsa {
	namespace compiler {

		class PrefixOperatorParser : public PrefixParser
		{
		public:
			Expression* parse(ElsaParser* parser, Token* token) override;
		};

	}
}
