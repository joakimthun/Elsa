#include "token.h"

namespace elsa {
	namespace compiler {

		Token::Token(TokenType type, const std::wstring& value, std::size_t line_number, const std::wstring& file_name)
			:
			type_(type),
			value_(value),
			line_number_(line_number),
			file_name_(file_name)
		{
		}

		Token::Token(TokenType type, wchar_t value, std::size_t line_number, const std::wstring& file_name)
			:
			type_(type),
			value_(std::wstring(&value)),
			line_number_(line_number),
			file_name_(file_name)
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

		const std::wstring& Token::get_file_name() const
		{
			return file_name_;
		}

		std::wstring Token::to_string(TokenType token)
		{
			switch (token)
			{
			case TokenType::Identifier:
				return L"identifier";
			case TokenType::Var:
				return L"var";
			case TokenType::IntegerLiteral:
				return L"integer literal";
			case TokenType::FloatLiteral:
				return L"float literal";
			case TokenType::CharLiteral:
				return L"char literal";
			case TokenType::BoolLiteral:
				return L"bool literal";
			case TokenType::StringLiteral:
				return L"string literal";
			case TokenType::Int:
				return L"int";
			case TokenType::Byte:
				return L"byte";
			case TokenType::Float:
				return L"float";
			case TokenType::Char:
				return L"char";
			case TokenType::Bool:
				return L"bool";
			case TokenType::Object:
				return L"object";
			case TokenType::Equals:
				return L"=";
			case TokenType::DoubleEquals:
				return L"==";
			case TokenType::NotEquals:
				return L"!=";
			case TokenType::Semicolon:
				return L";";
			case TokenType::Colon:
				return L":";
			case TokenType::Comma:
				return L",";
			case TokenType::Func:
				return L"fn";
			case TokenType::Return:
				return L"return";
			case TokenType::LBracket:
				return L"{";
			case TokenType::RBracket:
				return L"}";
			case TokenType::LSBracket:
				return L"[";
			case TokenType::RSBracket:
				return L"]";
			case TokenType::LParen:
				return L"(";
			case TokenType::RParen:
				return L")";
			case TokenType::Dot:
				return L".";
			case TokenType::Struct:
				return L"struct";
			case TokenType::This:
				return L"this";
			case TokenType::Void:
				return L"void";
			case TokenType::Plus:
				return L"+";
			case TokenType::PlusPlus:
				return L"++";
			case TokenType::PlusEquals:
				return L"+=";
			case TokenType::Minus:
				return L"-";
			case TokenType::MinusMinus:
				return L"--";
			case TokenType::MinusEquals:
				return L"-=";
			case TokenType::Asterix:
				return L"*";
			case TokenType::AsterixEquals:
				return L"*=";
			case TokenType::Slash:
				return L"/";
			case TokenType::SlashEquals:
				return L"/=";
			case TokenType::Exclamation:
				return L"!";
			case TokenType::LessThan:
				return L"<";
			case TokenType::LessThanEquals:
				return L"<=";
			case TokenType::GreaterThan:
				return L">";
			case TokenType::GreaterThanEquals:
				return L">=";
			case TokenType::Ampersand:
				return L"&";
			case TokenType::DoubleAmpersand:
				return L"&&";
			case TokenType::Percent:
				return L"%";
			case TokenType::VerticalBar:
				return L"|";
			case TokenType::DoubleVerticalBar:
				return L"||";
			case TokenType::New:
				return L"new";
			case TokenType::If:
				return L"if";
			case TokenType::Else:
				return L"else";
			case TokenType::For:
				return L"for";
			case TokenType::While:
				return L"while";
			case TokenType::Import:
				return L"import";
			case TokenType::Native:
				return L"native";
			case TokenType::Enum:
				return L"enum";
			default:
				throw ParsingException(L"Token.to_string: Unsupported token type");
			}
		}

	}
}
