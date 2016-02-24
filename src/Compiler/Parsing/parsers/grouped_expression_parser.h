#pragma once

#include "parser.h"
#include "../../ast/grouped_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class GroupedExpressionParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
