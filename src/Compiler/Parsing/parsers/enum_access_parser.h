#pragma once

#include "parser.h"
#include "../../ast/integer_literal_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class EnumAccessParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
