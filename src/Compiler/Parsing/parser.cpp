#include "parser.h"

namespace elsa {
	namespace compiler {

		Parser::Parser(Lexer* lexer) 
			:
			lexer_(std::unique_ptr<Lexer>(lexer))
		{
			next_token();
		}

		void Parser::next_token()
		{
			current_token_ = std::unique_ptr<Token>(lexer_->next_token());
		}

		void Parser::consume()
		{
			next_token();
		}

	}
}
