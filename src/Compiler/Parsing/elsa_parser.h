#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>

#include "../exceptions/parsing_exception.h"
#include "../lexing/lexer.h"
#include "../token.h"
#include "../program.h"
#include "../symbol_tables/struct_table.h"
#include "../symbol_tables/function_table.h"
#include "../types/builtin/builtin.h"
#include "precedence.h"
#include "parsers/prefix_operator_parser.h"
#include "parsers/identifier_parser.h"
#include "parsers/variable_declaration_parser.h"
#include "parsers/literal_parser.h"
#include "parsers/func_declaration_parser.h"
#include "parsers/binary_operator_parser.h"
#include "parsers/struct_declaration_parser.h"
#include "parsers/create_struct_parser.h"
#include "parsers/struct_access_parser.h"
#include "parsers/assignment_parser.h"
#include "parsers/func_call_parser.h"
#include "parsers/conditional_parser.h"
#include "parsers/loop_parser.h"
#include "parsers/postfix_operator_parser.h"
#include "parsers/return_parser.h"
#include "parsers/array_access_parser.h"
#include "parsers/type_cast_parser.h"
#include "parsers/anonymous_func_declaration_parser.h"
#include "parsers/grouped_expression_parser.h"
#include "parsers/enum_declaration_parser.h"
#include "parsers/enum_access_parser.h"
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
			ElsaParser(Lexer* lexer, bool load_default_imports = true);

			std::unique_ptr<Program> parse();
			std::unique_ptr<Expression> parse_statement();
			std::unique_ptr<Expression> parse_expression();
			std::unique_ptr<Expression> parse_expression(int precedence);
			ScopedExpression* current_scope();
			void push_new_scope(ScopedExpression* scope);
			void pop_current_scope();
			StructTable& struct_table();
			FunctionTable& function_table();
			TypeChecker& type_checker();
			void consume(TokenType type);
			void consume();
			Token* current_token();
			Token* peek_token();
			void set_current_type(const ElsaType* type);
			const ElsaType* current_type() const;
			void set_current_struct(StructDeclarationExpression* sde);
			const StructDeclarationExpression* current_struct() const;
			ElsaType* current_struct_type();
			const EnumDeclarationExpression* get_enum(const std::wstring& name) const;
			void add_enum(const EnumDeclarationExpression* enum_exp);

		private:
			ElsaParser(ElsaParser* parent, Lexer* lexer);

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
			void initialize_default_imports();
			void parse_import_statement();
			void import_source_file(const std::wstring& filename);
			void parse(Program* program);
			bool already_imported(const std::wstring& filename);
			std::vector<std::wstring>& imported_files_root();
			Program* get_root_program();
			bool is_member_access();

			std::unique_ptr<Program> program_;
			StructTable struct_table_;
			FunctionTable function_table_;
			ScopedExpression* current_scope_;
			std::unordered_map<TokenType, std::unique_ptr<Parser>> expression_parsers_;
			std::vector<std::unique_ptr<LL2Entry>> ll2_expression_parsers_;
			std::unordered_map<TokenType, std::unique_ptr<InfixParser>> infix_parsers_;
			std::unordered_map<TokenType, std::unique_ptr<Parser>> statement_parsers_;
			std::unique_ptr<Lexer> lexer_;
			std::unique_ptr<Token> current_token_;
			TypeChecker type_checker_;
			const ElsaType* current_type_;
			StructDeclarationExpression* current_struct_;
			std::vector<std::wstring> imported_files_;
			ElsaParser* parent_;
			std::unordered_map<std::wstring, const EnumDeclarationExpression*> enum_declarations_;
		};

	}
}