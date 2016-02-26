#include "enum_access_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> EnumAccessParser::parse(ElsaParser* parser)
		{
			auto enum_name = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::DoubleColon);
			auto enum_exp = parser->get_enum(enum_name);

			if (enum_exp == nullptr)
				throw ParsingException(L"No enum with the name '" + enum_name + L"' is defined", parser->current_token());

			auto member_name = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			int enum_value;
			if(!enum_exp->get_value(member_name, enum_value))
				throw ParsingException(L"The enum '" + enum_name + L"' has no member with the name '" + member_name + L"'");

			return std::make_unique<IntegerLiteralExpression>(enum_value);
		}

	}
}
