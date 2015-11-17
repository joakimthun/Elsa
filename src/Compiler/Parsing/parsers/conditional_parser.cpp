#include "conditional_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ConditionalParser::parse(ElsaParser* parser)
		{
			return std::make_unique<ConditionalExpression>();
		}

	}
}
