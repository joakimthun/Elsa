#pragma once

#include "prefix_parselet.h"
#include "../nodes/prefix_operator_expression.h"

namespace elsa {
	namespace compiler {

		class PrefixOperatorParselet : public PrefixParselet
		{
		public:
			Expression* parse(Parser* parser, Token* token) override;
		};

	}
}
