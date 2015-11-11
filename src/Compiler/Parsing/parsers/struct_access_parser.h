#pragma once

#include "parser.h"
#include "../../ast/struct_access_expression.h"
#include "../../ast/identifier_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class StructAccessParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;

		};

	}
}
