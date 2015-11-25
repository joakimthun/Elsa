#pragma once

#include "parser.h"
#include "../../ast/return_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class ReturnParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
