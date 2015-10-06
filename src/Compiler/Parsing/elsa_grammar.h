#pragma once

#include <memory>
#include <map>

#include "../lexing/token.h"
#include "parsers\parser.h"
#include "parsers\prefix_operator_parser.h"

namespace elsa {
	namespace compiler {

		class Parser;

		class ElsaGrammar
		{
		public:
			ElsaGrammar();

			Parser* get_parser(TokenType type);

		private:
			void register_prefix_op(TokenType type);
			void initialize_grammar();

			std::map<TokenType, std::unique_ptr<Parser>> parsers_;
		};

	}
}