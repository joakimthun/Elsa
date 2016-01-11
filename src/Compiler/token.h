#pragma once

#include <string>

namespace elsa {
	namespace compiler {

		enum class TokenType : int
		{
			END,
			Elsa,
			Identifier,
			Var,
			IntegerLiteral,
			FloatLiteral,
			CharLiteral,
			BoolLiteral,
			StringLiteral,
			Int,
			Float,
			Char,
			Bool,
			Equals,
			DoubleEquals,
			NotEquals,
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
			PlusPlus,
			PlusEquals,
			Minus,
			MinusMinus,
			MinusEquals,
			Asterix,
			AsterixEquals,
			Slash,
			SlashEquals,
			Exclamation,
			LessThan,
			LessThanEquals,
			GreaterThan,
			GreaterThanEquals,
			Ampersand,
			DoubleAmpersand,
			Percent,
			VerticalBar,
			DoubleVerticalBar,
			New,
			If,
			Else,
			Loop,
			Import,
			Native,
		};
		
		class Token
		{
		public:
			Token(TokenType type, const std::wstring& value, std::size_t line_number, const std::wstring& file_name);
			Token(TokenType type, wchar_t value, std::size_t line_number, const std::wstring& file_name);

			TokenType get_type() const;
			std::wstring get_value() const;
			std::size_t get_line_number() const;
			const std::wstring& get_file_name() const;

		private:
			TokenType type_;
			std::wstring value_;
			std::size_t line_number_;
			std::wstring file_name_;
		};

	}
}
