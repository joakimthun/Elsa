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
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;

		private:
			std::unique_ptr<FieldExpression> parse_field_expression(ElsaParser* parser);
			std::unique_ptr<FuncDeclarationExpression> parse_func_expression(ElsaParser* parser);
		};

	}
}
