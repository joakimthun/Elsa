#pragma once

#include <vector>
#include <memory>

#include "nodes\ast_node.h"

namespace elsa {
	namespace compiler {

		class Program
		{
		public:
			Program();

			void add_node(ASTNode* node);
		private:
			std::vector<std::unique_ptr<ASTNode>> nodes_;
		};

	}
}
