#pragma once

#include <memory>
#include <map>

#include "../lexing/token.h"
#include "parsers\prefix_parser.h"
#include "parsers\prefix_operator_parser.h"

namespace elsa {
	namespace compiler {

		class PrefixParser;

		class ElsaGrammar
		{
		public:
			ElsaGrammar();

			PrefixParser* get_prefix_parser(TokenType type);

		private:
			void register_prefix_op(TokenType type);
			void initialize_grammar();

			std::map<TokenType, std::unique_ptr<PrefixParser>> prefix_parsers_;
		};

	}
}