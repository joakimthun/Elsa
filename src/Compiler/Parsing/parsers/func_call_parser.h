#pragma once

#include <functional>

#include "parser.h"
#include "../../ast/func_call_expression.h"
#include "../elsa_parser.h"
#include "../../types/type_checker.h"

namespace elsa {
	namespace compiler {

		class FuncCallParser : public Parser
		{
		public:
			std::unique_ptr<Expression> parse(ElsaParser* parser) override;
			static std::unique_ptr<Expression> parse_member_call(ElsaParser* parser, const FuncDeclarationExpression* fde);

		private:
			static std::unique_ptr<Expression> parse(ElsaParser* parser, const FuncDeclarationExpression* fde);
		};

	}
}
