#include "program.h"

namespace elsa {
	namespace compiler {

		Program::Program(FunctionTable* function_table, StructTable* struct_table)
			:
			function_table_(function_table),
			struct_table_(struct_table)
		{}

		void Program::add_statement(std::unique_ptr<Expression> node)
		{
			statements_.push_back(std::move(node));
		}

		std::vector<std::unique_ptr<Expression>>& Program::get_statements()
		{
			return statements_;
		}

		FunctionTable * Program::function_table()
		{
			return function_table_;
		}

		StructTable * Program::struct_table()
		{
			return struct_table_;
		}

	}
}
