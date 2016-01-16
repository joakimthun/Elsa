#include "native_function_table.h"

namespace elsa {
	namespace compiler {

		NativeFunctionTable::NativeFunctionTable()
		{
			initialize();
		}

		void NativeFunctionTable::initialize()
		{
			add(L"Print", new NativeFunctionInfo(L"Print", 0));
			add(L"PrintLn", new NativeFunctionInfo(L"Print", 1));
			add(L"Equals", new NativeFunctionInfo(L"Equals", 2));
			add(L"AssertEq", new NativeFunctionInfo(L"AssertEq", 3));
		}

	}
}
