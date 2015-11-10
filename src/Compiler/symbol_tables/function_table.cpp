#include "function_table.h"

namespace elsa {
	namespace compiler {

		void FunctionTable::add_function(const std::wstring& name)
		{
			add(name, new FunctionSymbol(name));
		}

	}
}
