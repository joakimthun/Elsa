#pragma once

#include <memory>
#include <utility>

#include "../token.h"
#include "parsers\parser.h"

namespace elsa {
	namespace compiler {

		struct LL2Entry
		{
			LL2Entry(TokenType first, TokenType second, Parser* parser)
				:
				first(first),
				second(second),
				parser(std::unique_ptr<Parser>(parser))
			{}

			TokenType first;
			TokenType second;
			std::unique_ptr<Parser> parser;
		};

	}
}
