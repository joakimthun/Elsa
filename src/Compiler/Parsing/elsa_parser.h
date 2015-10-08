#pragma once

#include <memory>
#include <map>

#include "exceptions\parsing_exception.h"
#include "../lexing/lexer.h"
#include "../lexing/token.h"
#include "program.h"
#include "parsers\prefix_operator_parser.h"
#include "parsers\identifier_parser.h"
#include "parsers\variable_declaration_parser.h"
#include "parsers\literal_parser.h"
#include "parsers\func_declaration_parser.h"

namespace elsa {
	namespace compiler {

		class Expression;
		class Parser;

		class ElsaParser
		{
		public:
			ElsaParser(Lexer* lexer);

			Program* parse();
			void parse_statement();
			Expression* parse_expression();
			void consume(TokenType type);
			void consume();
			Token* current_token();

		private:
			void next_token();

			std::map<TokenType, std::unique_ptr<Parser>> parsers_;
			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
			Parser* get_parser(TokenType type);
			void register_parser(TokenType type, Parser* parser);
			void register_prefix_op(TokenType type);
			void initialize_grammar();
		};

	}
}