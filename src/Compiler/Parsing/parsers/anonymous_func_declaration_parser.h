#pragma once

#include <memory>

#include "parser.h"
#include "../../ast/func_declaration_expression.h"
#include "../../ast/argument_expression.h"
#include "../../ast/struct_declaration_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"
#include "util\string_util.h"

namespace elsa {
	namespace compiler {

		class AnonymousFuncDeclarationParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
		};

	}
}
