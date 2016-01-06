#pragma once

#include <memory>

#include "parser.h"
#include "../../ast/variable_declaration_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class VariableDeclarationParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;

		private:
			bool is_explicit(ElsaParser* parser);
			std::unique_ptr<ElsaType> get_explicit_type(ElsaParser* parser);
			void assert_is_valid_declaration(const ElsaType* expected, const ElsaType* actual, ElsaParser* parser);
		};

	}
}
