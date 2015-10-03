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
			Equals,
			Semicolon,
			Comma,
			Func,
			Return,
			LBracket,
			RBracket,
			LParen,
			RParen,
			Plus,
		};


		class Token
		{
		public:
			Token(TokenType type, const std::wstring& value);

			TokenType get_type() const;
			std::wstring get_value() const;

		private:
			TokenType type_;
			std::wstring value_;
		};

	}
}
