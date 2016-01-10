#pragma once

#include <memory>
#include <wctype.h>
#include <map>
#include <string>
#include <queue>
#include <utility>

#include "source_file.h"
#include "../token.h"
#include "exceptions\elsa_exception.h"

namespace elsa {
	namespace compiler {

		class Lexer
		{
		public:
			Lexer(SourceFile* file);

			std::unique_ptr<Token> next_token();
			Token* peek_token();

		private:

			void consume();
			void comment();
			std::unique_ptr<Token> alpha();
			std::unique_ptr<Token> number(bool negative = false);
			std::unique_ptr<Token> string();
			std::unique_ptr<Token> char_l();
			std::unique_ptr<Token> match_keyword(const std::wstring& value);
			void match(wchar_t c);
			std::unique_ptr<Token> match_token(wchar_t c, TokenType type);
			std::unique_ptr<Token> try_match_tokens(wchar_t first, wchar_t second, TokenType type);
			void register_keyword(const std::wstring keyword, TokenType type);
			void init_keywords();

			wchar_t current_char_;
			std::unique_ptr<SourceFile> file_;
			std::map<std::wstring, Token> keywords_;
			std::queue<std::unique_ptr<Token>> token_buffer_;
			std::size_t line_number_;

		};

	}
}