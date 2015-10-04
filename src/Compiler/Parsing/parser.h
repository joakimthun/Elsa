#pragma once

#include <memory>

#include "../lexing/lexer.h"
#include "../lexing/token.h"

namespace elsa {
	namespace compiler {

		class Parser
		{
		public:
			Parser(Lexer* lexer);


		private:
			void next_token();
			void consume();

			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
		};

	}
}