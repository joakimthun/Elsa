#include "elsa_invoke_parser.h"

namespace elsa {
	namespace compiler {

		Expression* ElsaInvokeParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::Elsa);

			auto function_name = parser->current_token()->get_value();

			parser->consume(TokenType::Identifier);
			return nullptr;
		}

	}
}

