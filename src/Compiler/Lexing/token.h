#pragma once

#include <string>

namespace elsa {
	namespace compiler {

		enum TokenType : int
		{
			END,
			Identifier,
			Var,
			IntegerLiteral,
			FloatLiteral,
			CharLiteral,
			BoolLiteral,
			StringLiteral,
			True,
			False,
			Int,
			Float,
			Char,
			Bool,
			String,
			Equals,
			Semicolon,
			Comma,
			Func,
			Return,
			LBracket,
			RBracket,
			LSBracket,
			RSBracket,
			LParen,
			RParen,
			Dot,
			Struct,
			This,
			Void,
			Plus,
			Hyphen,
			Asterix,
			Slash,
			Exclamation,
			LessThan,
			GreaterThen,
			Ampersand,
			Percent,
			VerticalBar,
		};


		class Token
		{
		public:
			Token(TokenType type, const std::wstring& value);
			Token(TokenType type, wchar_t value);

			TokenType get_type() const;
			std::wstring get_value() const;

		private:
			TokenType type_;
			std::wstring value_;
		};

	}
}
