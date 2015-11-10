#pragma once

#include "parser.h"
#include "../../ast/identifier_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class IdentifierParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
