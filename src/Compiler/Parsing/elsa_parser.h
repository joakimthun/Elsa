#pragma once

#include <memory>
#include <map>
#include <utility>
#include <vector>

#include "exceptions\parsing_exception.h"
#include "../lexing/lexer.h"
#include "../token.h"
#include "../program.h"
#include "../symbol_tables/struct_table.h"
#include "../symbol_tables/function_table.h"
#include "../types/builtin/builtin.h"
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
#include "parsers\struct_access_parser.h"
#include "parsers\assignment_parser.h"
#include "parsers\func_call_parser.h"
#include "parsers\conditional_parser.h"
#include "parsers\loop_parser.h"
#include "parsers\postfix_operator_parser.h"
#include "parsers\return_parser.h"
#include "parsers\array_declaration_parser.h"
#include "../types/type_checker.h"
#include "ll2_entry.h"

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
			ScopedExpression* current_scope();
			void set_current_scope(ScopedExpression* scope);
			void reset_current_scope();
			StructTable& struct_table();
			FunctionTable& function_table();
			TypeChecker& type_checker();
			void consume(TokenType type);
			void consume();
			Token* current_token();
			Token* peek_token();

		private:
			void next_token();

			Parser* get_expression_parser(TokenType type);
			Parser* get_ll2_expression_parser(TokenType first, TokenType second);
			Parser* get_statement_parser(TokenType type);
			InfixParser* get_infix_parser(TokenType type);
			int get_precedence();
			void register_expression_parser(TokenType type, Parser* parser);
			void register_ll2_expression_parser(TokenType first, TokenType second, Parser* parser);
			void register_statement_parser(TokenType type, Parser* parser);
			void register_infix_parser(TokenType type, InfixParser* parser);
			void register_prefix_parser(TokenType type);
			void register_postfix_parser(TokenType type, InfixParser* parser);
			void initialize_grammar();

			StructTable struct_table_;
			FunctionTable function_table_;
			ScopedExpression* current_scope_;
			std::map<TokenType, std::unique_ptr<Parser>> expression_parsers_;
			std::vector<std::unique_ptr<LL2Entry>> ll2_expression_parsers_;
			std::map<TokenType, std::unique_ptr<InfixParser>> infix_parsers_;
			std::map<TokenType, std::unique_ptr<Parser>> statement_parsers_;
			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
			TypeChecker type_checker_;
		};

	}
}