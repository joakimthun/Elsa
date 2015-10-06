#pragma once

#include <memory>
#include <map>

#include "../lexing/lexer.h"
#include "../lexing/token.h"
#include "program.h"
#include "nodes\expression.h"
#include "nodes\statement.h"
#include "parsers\prefix_parser.h"
#include "parsers\prefix_operator_parser.h"

namespace elsa {
	namespace compiler {

		class PrefixParser;

		class ElsaParser
		{
		public:
			ElsaParser(Lexer* lexer);

			Program* parse();
			void parse_statement();
			Expression* parse_expression();

		private:
			void next_token();
			void consume();
			PrefixParser* get_prefix_parser(TokenType type);
			void initialize_grammar();
			void register_prefix_op(TokenType type);

			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
			std::map<TokenType, std::unique_ptr<PrefixParser>> prefix_parsers_;
			Program* program_;
		};

	}
}