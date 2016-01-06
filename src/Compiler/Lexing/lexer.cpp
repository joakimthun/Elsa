#include "lexer.h"

namespace elsa {
	namespace compiler {

		Lexer::Lexer(SourceFile* file)
			:
			line_number_(1)
		{
			file_ = std::unique_ptr<SourceFile>(file);
			init_keywords();
			current_char_ = file_->next_char();
		}

		std::unique_ptr<Token> Lexer::next_token()
		{
			if (!token_buffer_.empty())
			{
				auto next = std::move(token_buffer_.front());
				token_buffer_.pop();
				return next;
			}

			while (file_->good())
			{
				if (iswspace(current_char_))
				{
					consume();
					continue;
				}
				else if(current_char_ == L'/' && file_->peek_char() == L'/')
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
				case L'"': {
					return string();
				}
				case L'\'': {
					return char_l();
				}
				case L'{': {
					return match_token(L'{', TokenType::LBracket);
				}
				case L'}': {
					return match_token(L'}', TokenType::RBracket);
				}
				case L'[': {
					return match_token(L'[', TokenType::LSBracket);
				}
				case L']': {
					return match_token(L']', TokenType::RSBracket);
				}
				case L'(': {
					return match_token(L'(', TokenType::LParen);
				}
				case L')': {
					return match_token(L')', TokenType::RParen);
				}
				case L';': {
					return match_token(L';', TokenType::Semicolon);
				}
				case L'.': {
					return match_token(L'.', TokenType::Dot);
				}
				case L',': {
					return match_token(L',', TokenType::Comma);
				}
				case L'=': {
					auto t = try_match_tokens(L'=', L'=', TokenType::DoubleEquals);
					if (t != nullptr)
						return t;

					return match_token(L'=', TokenType::Equals);
				}
				case L'+': {
					auto t = try_match_tokens(L'+', L'+', TokenType::PlusPlus);
					if (t != nullptr)
						return t;

					auto t2 = try_match_tokens(L'+', L'=', TokenType::PlusEquals);
					if (t2 != nullptr)
						return t2;

					return match_token(L'+', TokenType::Plus);
				}
				case L'-': {
					auto t = try_match_tokens(L'-', L'-', TokenType::MinusMinus);
					if (t != nullptr)
						return t;

					auto t2 = try_match_tokens(L'-', L'=', TokenType::MinusEquals);
					if (t2 != nullptr)
						return t2;

					return match_token(L'-', TokenType::Minus);
				}
				case L'*': {
					auto t = try_match_tokens(L'*', L'=', TokenType::AsterixEquals);
					if (t != nullptr)
						return t;

					return match_token(L'*', TokenType::Asterix);
				}
				case L'/': {
					auto t = try_match_tokens(L'/', L'=', TokenType::SlashEquals);
					if (t != nullptr)
						return t;

					return match_token(L'/', TokenType::Slash);
				}
				case L'!': {
					auto t = try_match_tokens(L'!', L'=', TokenType::NotEquals);
					if (t != nullptr)
						return t;

					return match_token(L'!', TokenType::Exclamation);
				}
				case L'<': {
					auto t = try_match_tokens(L'<', L'=', TokenType::LessThanEquals);
					if (t != nullptr)
						return t;

					return match_token(L'<', TokenType::LessThan);
				}
				case L'>': {
					auto t = try_match_tokens(L'>', L'=', TokenType::GreaterThanEquals);
					if (t != nullptr)
						return t;

					return match_token(L'>', TokenType::GreaterThan);
				}
				case L'%': {
					return match_token(L'%', TokenType::Percent);
				}
				case L'&': {
					auto t = try_match_tokens(L'&', L'&', TokenType::DoubleAmpersand);
					if (t != nullptr)
						return t;

					return match_token(L'&', TokenType::Ampersand);
				}
				case L'|': {
					auto t = try_match_tokens(L'|', L'|', TokenType::DoubleVerticalBar);
					if (t != nullptr)
						return t;

					return match_token(L'|', TokenType::VerticalBar);
				}
				default:
					throw ElsaException("Unknown token");
				}
			}

			return std::make_unique<Token>(TokenType::END, L"", line_number_, file_->get_file_name());
		}

		Token* Lexer::peek_token()
		{
			token_buffer_.push(next_token());
			return token_buffer_.back().get();
		}

		void Lexer::consume()
		{
			if (current_char_ == L'\n')
			{
				line_number_++;
			}

			current_char_ = file_->next_char();
		}

		void Lexer::comment()
		{
			while (file_->good() && current_char_ != L'\n')
			{
				consume();
			}
		}

		std::unique_ptr<Token> Lexer::alpha()
		{
			std::wstring value;
			while (file_->good() && (iswalnum(current_char_) || current_char_ == L'_'))
			{
				value += current_char_;
				consume();
			}

			auto keyword = match_keyword(value);
			if (keyword != nullptr)
				return keyword;

			return std::make_unique<Token>(TokenType::Identifier, value, line_number_, file_->get_file_name());
		}

		std::unique_ptr<Token> Lexer::number()
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

				return std::make_unique<Token>(TokenType::FloatLiteral, value, line_number_, file_->get_file_name());
			}

			return std::make_unique<Token>(TokenType::IntegerLiteral, value, line_number_, file_->get_file_name());
		}

		std::unique_ptr<Token> Lexer::string()
		{
			std::wstring value;
			consume();

			while (file_->good() && current_char_ != L'"')
			{
				value += current_char_;
				consume();
			}

			consume();

			return std::make_unique<Token>(TokenType::StringLiteral, value, line_number_, file_->get_file_name());
		}

		std::unique_ptr<Token> Lexer::char_l()
		{			
			std::wstring value;
			consume();

			while (file_->good() && current_char_ != L'\'')
			{
				value += current_char_;
				consume();
			}

			consume();

			return std::make_unique<Token>(TokenType::CharLiteral, value, line_number_, file_->get_file_name());
		}

		std::unique_ptr<Token> Lexer::match_keyword(const std::wstring& value)
		{
			auto it = keywords_.find(value);
			if (it != keywords_.end())
			{
				return std::make_unique<Token>(it->second.get_type(), it->second.get_value(), line_number_, file_->get_file_name());
			}

			return nullptr;
		}

		void Lexer::match(wchar_t c)
		{
			if (current_char_ != c)
				throw ElsaException("Could not match the current token");

			consume();
		}

		std::unique_ptr<Token> Lexer::match_token(wchar_t c, TokenType type)
		{
			match(c);
			return std::make_unique<Token>(type, c, line_number_, file_->get_file_name());
		}

		std::unique_ptr<Token> Lexer::try_match_tokens(wchar_t first, wchar_t second, TokenType type)
		{
			if (current_char_ == first && file_->peek_char() == second)
			{
				std::wstring value;
				value += current_char_;
				consume();
				value += current_char_;
				consume();

				return std::make_unique<Token>(type, value, line_number_, file_->get_file_name());
			}

			return nullptr;
		}

		void Lexer::register_keyword(const std::wstring keyword, TokenType type)
		{
			keywords_.insert(std::pair<std::wstring, Token>(keyword, Token(type, keyword, 0, file_->get_file_name())));
		}

		void Lexer::init_keywords()
		{
			register_keyword(L"func", TokenType::Func);
			register_keyword(L"return", TokenType::Return);
			register_keyword(L"var", TokenType::Var);
			register_keyword(L"int", TokenType::Int);
			register_keyword(L"float", TokenType::Float);
			register_keyword(L"char", TokenType::Char);
			register_keyword(L"bool", TokenType::Bool);
			register_keyword(L"true", TokenType::BoolLiteral);
			register_keyword(L"false", TokenType::BoolLiteral);
			register_keyword(L"struct", TokenType::Struct);
			register_keyword(L"this", TokenType::This);
			register_keyword(L"void", TokenType::Void);
			register_keyword(L"elsa", TokenType::Elsa);
			register_keyword(L"new", TokenType::New);
			register_keyword(L"if", TokenType::If);
			register_keyword(L"else", TokenType::Else);
			register_keyword(L"loop", TokenType::Loop);
			register_keyword(L"import", TokenType::Import);
		}
	}
}
