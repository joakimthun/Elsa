#include "loop_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> LoopParser::parse(ElsaParser* parser)
		{
			return std::make_unique<LoopExpression>();
		}

	}
}
