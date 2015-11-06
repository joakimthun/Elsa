#pragma once

#include <memory>

#include "parser.h"
#include "../../ast/struct_declaration_expression.h"
#include "../../ast/field_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class StructDeclarationParser : public Parser
		{
		public:
			Expression* parse(ElsaParser* parser) override;

		private:
			FieldExpression* parse_field_expression(ElsaParser* parser);
		};

	}
}
