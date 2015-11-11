#pragma once

#include <memory>
#include <utility>

#include "../../token.h"
#include "exceptions\parsing_exception.h"

namespace elsa {
	namespace compiler {

		class Expression;
		class ElsaParser;

		class InfixParser
		{
		public:
			virtual ~InfixParser() {};
			virtual std::unique_ptr<Expression> parse(ElsaParser* parser, std::unique_ptr<Expression> left) = 0;
			virtual int precedence() = 0;
		};

	}
}



