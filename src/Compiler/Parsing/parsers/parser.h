#pragma once

#include <memory>
#include <utility>

#include "../../token.h"

namespace elsa {
	namespace compiler {

		class Expression;
		class ElsaParser;

		class Parser
		{
		public:
			virtual ~Parser() {};
			virtual std::unique_ptr<Expression> parse(ElsaParser* parser) = 0;
		};

	}
}


