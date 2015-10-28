#pragma once

#include <memory>

#include "parser.h"
#include "../../ast/elsa_invoke_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class ElsaInvokeParser : public Parser
		{
		public:
			Expression* parse(ElsaParser* parser) override;
		};

	}
}
