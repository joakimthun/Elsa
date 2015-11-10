#include "prefix_operator_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> PrefixOperatorParser::parse(ElsaParser* parser)
		{
			auto op = parser->current_token()->get_type();
			parser->consume(op);

			auto right = parser->parse_expression();
			return std::make_unique<PrefixOperatorExpression>(op, std::move(right));
		}

	}
}
