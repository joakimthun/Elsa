#include "create_struct_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> CreateStructParser::parse(ElsaParser* parser)
		{
			parser->consume(TokenType::New);

			auto struct_name = parser->current_token()->get_value();

			parser->consume(TokenType::Identifier);

			return std::make_unique<CreateStructExpression>(struct_name);
		}

	}
}

