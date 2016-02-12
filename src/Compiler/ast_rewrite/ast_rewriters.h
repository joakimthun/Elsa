#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "ast_rewriter.h"
#include "../program.h"
#include "closure\closure_rewrite_visitor.h"

namespace elsa {
	namespace compiler {

		class Program;
		class ElsaParser;

		class ASTRewrites
		{
		public:
			ASTRewrites(Program* program, ElsaParser* parser);
			void execute();

		private:
			std::vector<std::unique_ptr<ASTRewriter>> rewriters_;
			Program* program_;
		};
	}
}
