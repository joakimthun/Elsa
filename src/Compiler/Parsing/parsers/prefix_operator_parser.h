#pragma once

#include "parser.h"
#include "../../ast/prefix_operator_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class PrefixOperatorParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
