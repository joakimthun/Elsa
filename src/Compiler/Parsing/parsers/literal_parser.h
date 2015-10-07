#pragma once

#include <string>

#include "parser.h"
#include "../ast/integer_literal_expression.h"
#include "../ast/float_literal_expression.h"
#include "../ast/char_literal_expression.h"
#include "../ast/bool_literal_expression.h"
#include "../ast/string_literal_expression.h"
#include "../elsa_parser.h"
#include "exceptions\parsing_exception.h"

namespace elsa {
	namespace compiler {

		class LiteralParser : public Parser
		{
		public:
			Expression* parse(ElsaParser* parser) override;

		};

	}
}
