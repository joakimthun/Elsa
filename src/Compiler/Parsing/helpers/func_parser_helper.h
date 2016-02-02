#pragma once

#include <memory>

#include "../../ast/func_declaration_expression.h"
#include "../../ast/argument_expression.h"
#include "../../ast/struct_declaration_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"
#include "util\string_util.h"

namespace elsa {
	namespace compiler {

		class FuncParserHelper
		{
		public:
			static std::unique_ptr<FuncDeclarationExpression> parse_signature(ElsaParser* parser, bool anonymous, StructDeclarationExpression* parent);
		};

	}
}
