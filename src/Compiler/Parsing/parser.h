#pragma once

#include <memory>

#include "../lexing/lexer.h"
#include "../lexing/token.h"
#include "program.h"

namespace elsa {
	namespace compiler {

		class Parser
		{
		public:
			Parser(Lexer* lexer);

			Program* parse();

		private:
			void next_token();
			void consume();
			void parse_statement();

			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
			Program* program_;
		};

	}
}