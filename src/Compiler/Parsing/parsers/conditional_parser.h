#pragma once

#include "parser.h"
#include "../../ast/conditional_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class ConditionalParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
