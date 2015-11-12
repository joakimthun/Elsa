#pragma once

#include <memory>

#include "infix_parser.h"
#include "../../ast/assignment_expression.h"
#include "../elsa_parser.h"
#include "./../precedence.h"

namespace elsa {
	namespace compiler {

		class AssignmentParser : public InfixParser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser, std::unique_ptr<Expression> left) override;
			int precedence() override;
		};

	}
}

