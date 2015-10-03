#include "token.h"

namespace elsa {
	namespace compiler {

		Token::Token(TokenType type, const std::wstring& value)
			:
			type_(type),
			value_(value)
		{
		}

		Token::Token(TokenType type, wchar_t value)
			:
			type_(type),
			value_(std::wstring(&value))
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

	}
}
