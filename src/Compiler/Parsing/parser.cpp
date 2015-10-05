#include "parser.h"

namespace elsa {
	namespace compiler {

		Parser::Parser(Lexer* lexer) 
			:
			lexer_(std::unique_ptr<Lexer>(lexer))
		{
			initialize_grammar();
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

		void Parser::parse_statement()
		{

		}

		Expression* Parser::parse_expression()
		{
			auto prefix_parselet = get_prefix_parselet(current_token_->get_type());


			return nullptr;
		}

		void Parser::next_token()
		{
			current_token_ = std::unique_ptr<Token>(lexer_->next_token());
		}

		void Parser::consume()
		{
			next_token();
		}

		PrefixParselet* Parser::get_prefix_parselet(TokenType type)
		{
			auto it = prefix_parselets_.find(type);
			if (it != prefix_parselets_.end())
			{
				return it->second.get();
			}
		
			return nullptr;
		}

		void Parser::initialize_grammar()
		{
			register_prefix_op(TokenType::Exclamation);
		}

		void Parser::register_prefix_op(TokenType type)
		{
			prefix_parselets_.insert(std::pair<TokenType, std::unique_ptr<PrefixParselet>>(type, std::unique_ptr<PrefixParselet>(new PrefixOperatorParselet())));
		}

	}
}
