#include "token.h"

namespace elsa {
	namespace compiler {

		Token::Token(TokenType type, const std::wstring& value, std::size_t line_number)
			:
			type_(type),
			value_(value),
			line_number_(line_number)
		{
		}

		Token::Token(TokenType type, wchar_t value, std::size_t line_number)
			:
			type_(type),
			value_(std::wstring(&value)),
			line_number_(line_number)
		{
		}

		TokenType Token::get_type() const
		{
			return type_;
		}

		std::wstring Token::get_value() const
		{
			return value_;
		}

		std::size_t Token::get_line_number() const
		{
			return line_number_;
		}

	}
}
