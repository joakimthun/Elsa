#include "parser.h"

namespace elsa {
	namespace compiler {

		Parser::Parser(Lexer* lexer) 
			:
			lexer_(std::unique_ptr<Lexer>(lexer))
		{
		}

		Program* Parser::parse()
		{
			program_ = new Program();

			next_token();
			while (current_token_->get_type() != TokenType::END)
			{
				parse_statement();
			}

			return program_;
		}

		void Parser::next_token()
		{
			current_token_ = std::unique_ptr<Token>(lexer_->next_token());
		}

		void Parser::consume()
		{
			next_token();
		}

		void Parser::parse_statement()
		{

		}

	}
}
