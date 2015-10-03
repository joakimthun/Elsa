#include "lexer.h"

namespace elsa {
	namespace compiler {

		Lexer::Lexer(SourceFile* file)
		{
			file_ = std::unique_ptr<SourceFile>(file);
		}

		Token Lexer::next_token()
		{
			return Token(TokenType::Var, std::wstring(L"var"));
		}

	}
}
