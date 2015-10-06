#pragma once

#include <memory>
#include <map>

#include "../lexing/lexer.h"
#include "../lexing/token.h"
#include "program.h"
#include "elsa_grammar.h"
#include "nodes\expression.h"
#include "nodes\statement.h"

namespace elsa {
	namespace compiler {

		class ElsaGrammar;

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

			std::unique_ptr<ElsaGrammar> grammar_;
			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
			Program* program_;
		};

	}
}