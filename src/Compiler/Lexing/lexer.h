#pragma once

#include <memory>
#include <wctype.h>
#include <map>
#include <string>

#include "source_file.h"
#include "token.h"
#include "exceptions\elsa_exception.h"

namespace elsa {
	namespace compiler {

		class Lexer
		{
		public:
			Lexer(SourceFile* file);

			Token* next_token();

		private:

			void init_keywords();
			void consume();
			void comment();
			Token* alpha();
			Token* match_keyword(const std::wstring& value);
			void match(wchar_t c);

			wchar_t current_char_;
			std::unique_ptr<SourceFile> file_;
			std::map<std::wstring, Token> keywords_;
		};

	}
}