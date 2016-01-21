#pragma once

#include <memory>

#include "parser.h"
#include "../../ast/func_declaration_expression.h"
#include "../../ast/argument_expression.h"
#include "../../ast/struct_declaration_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class FuncDeclarationParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
			static std::unique_ptr<Expression> parse_member(ElsaParser* parser, StructDeclarationExpression* parent);

		private:
			static std::unique_ptr<Expression> parse_internal(ElsaParser* parser, StructDeclarationExpression* parent);
		};

	}
}
