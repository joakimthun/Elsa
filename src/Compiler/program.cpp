#include "program.h"

namespace elsa {
	namespace compiler {

		Program::Program() {}

		void Program::add_statement(std::unique_ptr<Expression> node)
		{
			statements_.push_back(std::move(node));
		}

		void Program::add_function(FunctionSymbol* function)
		{
			auto fs = std::unique_ptr<FunctionSymbol>(function);

			if (functions_.has_entry(function->get_name()))
				throw ParsingException("A global function with the same name has already been delared");

			functions_.add(function->get_name(), fs.release());
		}

		std::vector<std::unique_ptr<Expression>>& Program::get_statements()
		{
			return statements_;
		}

	}
}
