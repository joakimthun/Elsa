#include "prefix_operator_parselet.h"

namespace elsa {
	namespace compiler {

		Expression* PrefixOperatorParselet::parse(Parser* parser, Token* token)
		{
			auto right = parser->parse_expression();
			return new PrefixOperatorExpression(token->get_type(), right);
		}

	}
}
