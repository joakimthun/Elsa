#include "identifier_parser.h"

namespace elsa {
	namespace compiler {

		Expression* IdentifierParser::parse(ElsaParser* parser, Token* token)
		{
			auto identifier = parser->current_token()->get_value();
			parser->consume(TokenType::Identifier);

			return new IdentifierExpression(identifier);
		}

	}
}
