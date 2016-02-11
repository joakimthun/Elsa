#include "program.h"

namespace elsa {
	namespace compiler {

		void Program::add_statement(std::unique_ptr<Expression> node)
		{
			statements_.push_back(std::move(node));
		}

		void Program::add_statement_front(std::unique_ptr<Expression> node)
		{
			statements_.insert(statements_.begin(), std::move(node));
		}

		std::vector<std::unique_ptr<Expression>>& Program::get_statements()
		{
			return statements_;
		}

	}
}
