#include "create_struct_parser.h"

namespace elsa {
	namespace compiler {

		Expression* CreateStructParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::New);

			auto struct_name = parser->current_token()->get_value();

			parser->consume(TokenType::Identifier);
			parser->consume(TokenType::Semicolon);

			return new CreateStructExpression(struct_name);
		}

	}
}

