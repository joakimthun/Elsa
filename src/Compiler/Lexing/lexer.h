#pragma once

#include <memory>
#include <wctype.h>
#include <map>
#include <string>

#include "source_file.h"
#include "../token.h"
#include "exceptions\elsa_exception.h"

namespace elsa {
	namespace compiler {

		class Lexer
		{
		public:
			Lexer(SourceFile* file);

			Token* next_token();

		private:

			void consume();
			void comment();
			Token* alpha();
			Token* number();
			Token* string();
			Token* char_l();
			Token* match_keyword(const std::wstring& value);
			void match(wchar_t c);
			Token* match_token(wchar_t c, TokenType type);
			Token* try_match_tokens(wchar_t first, wchar_t second, TokenType type);
			void register_keyword(const std::wstring keyword, TokenType type);
			void init_keywords();

			wchar_t current_char_;
			std::unique_ptr<SourceFile> file_;
			std::map<std::wstring, Token> keywords_;
		};

	}
}