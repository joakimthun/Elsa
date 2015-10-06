#include "prefix_operator_parser.h"

namespace elsa {
	namespace compiler {

		Expression* PrefixOperatorParser::parse(ElsaParser* parser, Token* token)
		{
			auto right = parser->parse_expression();
			return new PrefixOperatorExpression(token->get_type(), right);
		}

	}
}
