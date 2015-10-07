#include "prefix_operator_parser.h"

namespace elsa {
	namespace compiler {

		Expression* PrefixOperatorParser::parse(ElsaParser* parser)
		{
			auto op = parser->current_token()->get_type();
			parser->consume(op);

			auto right = parser->parse_expression();
			return new PrefixOperatorExpression(op, right);
		}

	}
}
