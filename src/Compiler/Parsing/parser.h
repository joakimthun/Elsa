#pragma once

#include <memory>
#include <map>

#include "../lexing/lexer.h"
#include "../lexing/token.h"
#include "program.h"
#include "nodes\expression.h"
#include "nodes\statement.h"
#include "parselets\prefix_parselet.h"
#include "parselets\prefix_operator_parselet.h"

namespace elsa {
	namespace compiler {

		class PrefixParselet;

		class Parser
		{
		public:
			Parser(Lexer* lexer);

			Program* parse();
			void parse_statement();
			Expression* parse_expression();

		private:
			void next_token();
			void consume();
			PrefixParselet* get_prefix_parselet(TokenType type);
			void initialize_grammar();
			void register_prefix_op(TokenType type);

			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
			std::map<TokenType, std::unique_ptr<PrefixParselet>> prefix_parselets_;
			Program* program_;
		};

	}
}