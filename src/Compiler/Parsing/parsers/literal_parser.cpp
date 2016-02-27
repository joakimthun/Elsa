#include "literal_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> LiteralParser::parse(ElsaParser* parser)
		{
			auto token_value = parser->current_token()->get_value();

			switch (parser->current_token()->get_type())
			{
			case TokenType::IntegerLiteral: {
				parser->consume(TokenType::IntegerLiteral);
				return std::make_unique<IntegerLiteralExpression>(std::stoi(token_value, nullptr));
			}
			case TokenType::FloatLiteral: {
				parser->consume(TokenType::FloatLiteral);
				return std::make_unique<FloatLiteralExpression>(std::stof(token_value, nullptr));
			}
			case TokenType::CharLiteral: {
				parser->consume(TokenType::CharLiteral);
				return std::make_unique<CharLiteralExpression>(token_value[0]);
			}
			case TokenType::BoolLiteral: {
				parser->consume(TokenType::BoolLiteral);
				return std::make_unique<BoolLiteralExpression>(token_value == L"true");
			}
			case TokenType::StringLiteral: {
				parser->consume(TokenType::StringLiteral);
				return std::make_unique<StringLiteralExpression>(token_value);
			}
			case TokenType::HexLiteral: {
				parser->consume(TokenType::HexLiteral);
				return std::make_unique<IntegerLiteralExpression>(std::stoi(token_value, nullptr, 16));
			}
			default:
				throw ParsingException(L"Invalid token.", parser->current_token());
			}
		}
	}
}
