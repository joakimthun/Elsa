#include "token.h"

namespace elsa {
	namespace compiler {

		Token::Token(TokenType type, const std::wstring& value)
			:
			type_(type),
			value_(value)
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
