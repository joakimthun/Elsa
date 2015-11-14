#include "function_table.h"

namespace elsa {
	namespace compiler {

		void FunctionTable::add_function(const FuncDeclarationExpression* expression)
		{
			add(expression->get_name(), new FunctionSymbol(expression));
		}

	}
}
