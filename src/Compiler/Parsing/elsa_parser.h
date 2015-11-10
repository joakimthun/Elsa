#pragma once

#include <memory>
#include <map>
#include <utility>

#include "exceptions\parsing_exception.h"
#include "../lexing/lexer.h"
#include "../token.h"
#include "../program.h"
#include "precedence.h"
#include "parsers\prefix_operator_parser.h"
#include "parsers\identifier_parser.h"
#include "parsers\variable_declaration_parser.h"
#include "parsers\literal_parser.h"
#include "parsers\func_declaration_parser.h"
#include "parsers\binary_operator_parser.h"
#include "parsers\elsa_invoke_parser.h"
#include "parsers\struct_declaration_parser.h"
#include "parsers\create_struct_parser.h"

namespace elsa {
	namespace compiler {

		class Expression;
		class Parser;
		class InfixParser;

		class ElsaParser
		{
		public:
			ElsaParser(Lexer* lexer);

			std::unique_ptr<Program> parse();
			std::unique_ptr<Expression> parse_statement();
			std::unique_ptr<Expression> parse_expression();
			std::unique_ptr<Expression> parse_expression(int precedence);
			void consume(TokenType type);
			void consume();
			Token* current_token();

		private:
			void next_token();

			Parser* get_expression_parser(TokenType type);
			Parser* get_statement_parser(TokenType type);
			InfixParser* get_infix_parser(TokenType type);
			int get_precedence();
			void register_expression_parser(TokenType type, Parser* parser);
			void register_statement_parser(TokenType type, Parser* parser);
			void register_infix_parser(TokenType type, InfixParser* parser);
			void register_prefix_parser(TokenType type);
			void initialize_grammar();

			std::map<TokenType, std::unique_ptr<Parser>> expression_parsers_;
			std::map<TokenType, std::unique_ptr<InfixParser>> infix_parsers_;
			std::map<TokenType, std::unique_ptr<Parser>> statement_parsers_;
			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
		};

	}
}