#pragma once

#include <memory>

#include "parser.h"
#include "../../ast/create_struct_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class CreateStructParser : public Parser
		{
		public:
			Expression* parse(ElsaParser* parser) override;
		};

	}
}
