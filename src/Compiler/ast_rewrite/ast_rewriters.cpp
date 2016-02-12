#include "ast_rewriters.h"

namespace elsa {
	namespace compiler {

		ASTRewrites::ASTRewrites(Program* program, ElsaParser* parser)
			:
			program_(program)
		{
			rewriters_.push_back(std::make_unique<ClosureRewriteVisitor>(program, parser));
		}

		void ASTRewrites::execute()
		{
			for (auto& rewriter : rewriters_)
			{
				rewriter->rewrite();

				for (auto& s : rewriter->get_new_statements())
				{
					program_->add_statement_front(std::move(s));
				}
			}
		}
	}
}

