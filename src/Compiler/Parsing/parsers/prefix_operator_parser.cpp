#include "prefix_operator_parser.h"

namespace elsa {
	namespace compiler {

		Expression* PrefixOperatorParser::parse(ElsaParser* parser, Token* token)
		{
			auto op = token->get_type();
			parser->consume(op);

			auto right = parser->parse_expression();
			return new PrefixOperatorExpression(op, right);
		}

	}
}
