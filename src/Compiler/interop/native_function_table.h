#pragma once

#include "../symbol_tables/symbol_table.h"
#include "native_function_info.h"

namespace elsa {
	namespace compiler {

		class NativeFunctionTable : public SymbolTable<std::wstring, NativeFunctionInfo>
		{
		public:
			NativeFunctionTable();
			
		private:
			void initialize();
		};

	}
}
