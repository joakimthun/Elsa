#include "elsa_parser.h"

namespace elsa {
	namespace compiler {

		ElsaParser::ElsaParser(Lexer* lexer)
			:
			lexer_(std::unique_ptr<Lexer>(lexer))
		{
			initialize_grammar();
			next_token();
		}

		Program* ElsaParser::parse()
		{
			auto program = new Program();

			while (current_token_->get_type() != TokenType::END)
			{
				parse_statement();
			}

			return program;
		}

		void ElsaParser::parse_statement()
		{

		}

		Expression* ElsaParser::parse_expression()
		{
			auto parser = get_parser(current_token_->get_type());
			
			if (parser == nullptr)
				throw ParsingException("Invalid token");
			
			return parser->parse(this, current_token_.get());
		}

		void ElsaParser::consume(TokenType type)
		{
			next_token();
		}

		Token* ElsaParser::current_token()
		{
			return current_token_.get();
		}

		void ElsaParser::next_token()
		{
			current_token_ = std::unique_ptr<Token>(lexer_->next_token());
		}

		Parser* ElsaParser::get_parser(TokenType type)
		{
			auto it = parsers_.find(type);
			if (it != parsers_.end())
			{
				return it->second.get();
			}

			return nullptr;
		}

		void ElsaParser::register_parser(TokenType type, Parser* parser)
		{
			parsers_.insert(std::pair<TokenType, std::unique_ptr<Parser>>(type, std::unique_ptr<Parser>(parser)));
		}

		void ElsaParser::register_prefix_op(TokenType type)
		{
			register_parser(type, new PrefixOperatorParser());
		}

		void ElsaParser::initialize_grammar()
		{
			register_parser(TokenType::Identifier, new IdentifierParser());

			register_prefix_op(TokenType::Exclamation);
		}
	}
}
