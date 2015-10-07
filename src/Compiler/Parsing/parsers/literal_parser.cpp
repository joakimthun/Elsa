#include "literal_parser.h"

namespace elsa {
	namespace compiler {

		Expression* LiteralParser::parse(ElsaParser* parser)
		{
			auto token_value = parser->current_token()->get_value();

			switch (parser->current_token()->get_type())
			{
			case TokenType::IntegerLiteral: {
				parser->consume(TokenType::IntegerLiteral);
				return new IntegerLiteralExpression(std::stoi(token_value, nullptr));
			}
			case TokenType::FloatLiteral: {
				parser->consume(TokenType::FloatLiteral);
				return new FloatLiteralExpression(std::stof(token_value, nullptr));
			}
			case TokenType::CharLiteral: {
				parser->consume(TokenType::CharLiteral);
				return new CharLiteralExpression(token_value[0]);
			}
			case TokenType::BoolLiteral: {
				parser->consume(TokenType::BoolLiteral);
				return new BoolLiteralExpression(token_value == L"true");
			}
			case TokenType::StringLiteral: {
				parser->consume(TokenType::StringLiteral);
				return new StringLiteralExpression(token_value);
			}
			default:
				throw ParsingException("Invalid token.");
			}
		}
	}
}
