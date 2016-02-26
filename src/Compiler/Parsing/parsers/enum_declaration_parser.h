#pragma once

#include <string>

#include "parser.h"
#include "../../ast/enum_declaration_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class EnumDeclarationParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;

		};

	}
}
