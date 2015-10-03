#include "lexer.h"

namespace elsa {
	namespace compiler {

		Lexer::Lexer(SourceFile* file)
		{
			file_ = std::unique_ptr<SourceFile>(file);
			init_keywords();
			current_char_ = file_->next_char();
		}

		Token* Lexer::next_token()
		{
			while (file_->good())
			{
				if (iswspace(current_char_))
				{
					consume();
				}
				else if(current_char_ == L'/')
				{
					comment();
				}
				else if(iswalpha(current_char_))
				{
					return alpha();
				}

				switch (current_char_)
				{
				case L'{': {
					match(L'{');
					return new Token(TokenType::LBracket, L"{");
				}
				case L'}': {
					match(L'}');
					return new Token(TokenType::RBracket, L"}");
				}
				case L'(': {
					match(L'(');
					return new Token(TokenType::LParen, L"(");
				}
				case L')': {
					match(L')');
					return new Token(TokenType::RParen, L")");
				}
				case L',': {
					match(L',');
					return new Token(TokenType::Comma, L",");
				}
				case L'+': {
					match(L'+');
					return new Token(TokenType::Plus, L"+");
				}
				case L';': {
					match(L';');
					return new Token(TokenType::Semicolon, L";");
				}
				default:
					//throw ElsaException("Unknown token");
					break;
				}
			}

			return new Token(TokenType::END, L"");
		}

		void Lexer::init_keywords()
		{
			keywords_.insert(std::pair<std::wstring, Token>(L"func", Token(TokenType::Func, L"func")));
			keywords_.insert(std::pair<std::wstring, Token>(L"return", Token(TokenType::Return, L"return")));
			keywords_.insert(std::pair<std::wstring, Token>(L"var", Token(TokenType::Var, L"var")));
		}

		void Lexer::consume()
		{
			current_char_ = file_->next_char();
		}

		void Lexer::comment()
		{
			while (file_->good() && current_char_ != L'\n')
			{
				consume();
			}
		}

		Token* Lexer::alpha()
		{
			std::wstring value;
			while (file_->good() && iswalnum(current_char_))
			{
				value += current_char_;
				consume();
			}

			auto keyword = match_keyword(value);
			if (keyword != nullptr)
				return keyword;

			return new Token(TokenType::Identifier, value);
		}

		Token* Lexer::match_keyword(const std::wstring& value)
		{
			auto it = keywords_.find(value);
			if (it != keywords_.end())
			{
				return new Token(it->second);
			}

			return nullptr;
		}

		void Lexer::match(wchar_t c)
		{
			if (current_char_ != c)
				throw ElsaException("Could not match the current token");

			consume();
		}

	}
}
