#pragma once

#include "../ast/expression.h"

namespace elsa {
	namespace compiler {

		class ASTRewriter
		{
		public:
			virtual ~ASTRewriter() {};
			virtual void rewrite() = 0;
			virtual std::vector<std::unique_ptr<Expression>>& get_new_statements() = 0;
		};
	}
}