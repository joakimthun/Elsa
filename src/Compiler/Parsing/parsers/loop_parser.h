#pragma once

#include "parser.h"
#include "../../ast/loop_expression.h"
#include "../../ast/variable_declaration_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class LoopParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
