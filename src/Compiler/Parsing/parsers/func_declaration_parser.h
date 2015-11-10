#pragma once

#include <memory>

#include "parser.h"
#include "../../ast/func_declaration_expression.h"
#include "../../ast/argument_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"
#include "exceptions\parsing_exception.h"

namespace elsa {
	namespace compiler {

		class FuncDeclarationParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
