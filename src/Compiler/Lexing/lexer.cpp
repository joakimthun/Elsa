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
					continue;
				}
				else if(current_char_ == L'/')
				{
					comment();
					continue;
				}
				else if(iswalpha(current_char_))
				{
					return alpha();
				}
				else if (iswdigit(current_char_))
				{
					return number();
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
				case L'.': {
					match(L'.');
					return new Token(TokenType::Dot, L".");
				}
				default:
					throw ElsaException("Unknown token");
				}
			}

			return new Token(TokenType::END, L"");
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

		Token* Lexer::number()
		{
			std::wstring value;
			while (file_->good() && iswdigit(current_char_))
			{
				value += current_char_;
				consume();
			}

			if (current_char_ == L'.')
			{
				value += current_char_;
				consume();

				while (file_->good() && iswdigit(current_char_))
				{
					value += current_char_;
					consume();
				}

				return new Token(TokenType::FloatLiteral, value);
			}

			return new Token(TokenType::IntegerLiteral, value);
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

		void Lexer::register_keyword(const std::wstring keyword, TokenType type)
		{
			keywords_.insert(std::pair<std::wstring, Token>(keyword, Token(type, keyword)));
		}

		void Lexer::init_keywords()
		{
			register_keyword(L"func", TokenType::Func);
			register_keyword(L"return", TokenType::Return);
			register_keyword(L"var", TokenType::Var);
			register_keyword(L"int", TokenType::Int);
			register_keyword(L"float", TokenType::Float);
			register_keyword(L"string", TokenType::String);
			register_keyword(L"char", TokenType::Char);
			register_keyword(L"bool", TokenType::Bool);
			register_keyword(L"true", TokenType::True);
			register_keyword(L"false", TokenType::False);
		}
	}
}
