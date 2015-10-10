#pragma once

#include <memory>

#include "parser.h"
#include "../ast/func_declaration_expression.h"
#include "../ast/argument_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class FuncDeclarationParser : public Parser
		{
		public:
			Expression* parse(ElsaParser* parser) override;
		};

	}
}
