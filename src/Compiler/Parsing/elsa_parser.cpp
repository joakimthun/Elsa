#include "elsa_parser.h"

namespace elsa {
	namespace compiler {

		ElsaParser::ElsaParser(Lexer* lexer)
			:
			lexer_(std::unique_ptr<Lexer>(lexer))
		{
			initialize_grammar();
		}

		Program* ElsaParser::parse()
		{
			program_ = new Program();

			next_token();
			while (current_token_->get_type() != TokenType::END)
			{
				parse_statement();
			}

			return program_;
		}

		void ElsaParser::parse_statement()
		{

		}

		Expression* ElsaParser::parse_expression()
		{
			auto prefix_parselet = get_prefix_parser(current_token_->get_type());


			return nullptr;
		}

		void ElsaParser::next_token()
		{
			current_token_ = std::unique_ptr<Token>(lexer_->next_token());
		}

		void ElsaParser::consume()
		{
			next_token();
		}

		PrefixParser* ElsaParser::get_prefix_parser(TokenType type)
		{
			auto it = prefix_parsers_.find(type);
			if (it != prefix_parsers_.end())
			{
				return it->second.get();
			}
		
			return nullptr;
		}

		void ElsaParser::initialize_grammar()
		{
			register_prefix_op(TokenType::Exclamation);
		}

		void ElsaParser::register_prefix_op(TokenType type)
		{
			prefix_parsers_.insert(std::pair<TokenType, std::unique_ptr<PrefixParser>>(type, std::unique_ptr<PrefixParser>(new PrefixOperatorParser())));
		}

	}
}
