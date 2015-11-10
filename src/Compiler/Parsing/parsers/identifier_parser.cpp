#include "identifier_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> IdentifierParser::parse(ElsaParser* parser)
		{
			auto identifier = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			return std::make_unique<IdentifierExpression>(identifier);
		}

	}
}
