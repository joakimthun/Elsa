#include "Program.h"

namespace elsa {
	namespace compiler {

		Program::Program() {}

		void Program::add_node(ASTNode* node)
		{
			nodes_.push_back(std::unique_ptr<ASTNode>(node));
		}

	}
}
