#include "program.h"

namespace elsa {
	namespace compiler {

		Program::Program() {}

		void Program::add_expression(Expression* node)
		{
			nodes_.push_back(std::unique_ptr<Expression>(node));
		}

	}
}
