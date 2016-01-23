#pragma once

#include "parser.h"
#include "../../ast/type_cast_expression.h"
#include "../elsa_parser.h"

namespace elsa {
	namespace compiler {

		class TypeCastParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;

		private:
			ElsaType* get_dest_type(ElsaParser* parser);
		};

	}
}
