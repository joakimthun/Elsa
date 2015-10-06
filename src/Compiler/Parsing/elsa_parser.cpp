#include "elsa_parser.h"

namespace elsa {
	namespace compiler {

		ElsaParser::ElsaParser(Lexer* lexer)
			:
			lexer_(std::unique_ptr<Lexer>(lexer)),
			grammar_(std::unique_ptr<ElsaGrammar>(new ElsaGrammar()))
		{
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
			auto parser = grammar_->get_parser(current_token_->get_type());

			if (parser == nullptr)
				throw ParsingException("Invalid token");

			auto expression = parser->parse(this, current_token_.get());

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


	}
}
