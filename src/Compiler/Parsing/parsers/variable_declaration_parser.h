#pragma once

#include "parser.h"
#include "../../ast/variable_declaration_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class VariableDeclarationParser : public Parser
		{
		public:
			Expression* parse(ElsaParser* parser) override;
		};

	}
}
