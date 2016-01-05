#pragma once

#include <memory>
#include <utility>

#include "parser.h"
#include "../../ast/create_struct_expression.h"
#include "../../ast/array_declaration_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class CreateStructParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;

		private:
			std::unique_ptr<Expression> parse_array(ElsaParser* parser);
			bool is_array(ElsaParser* parser);
		};

	}
}
