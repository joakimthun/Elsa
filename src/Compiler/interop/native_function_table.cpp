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
			add(L"ReferenceEquals", new NativeFunctionInfo(L"ReferenceEquals", 4));
			add(L"CreateWindow", new NativeFunctionInfo(L"CreateWindow", 5));
			add(L"OpenWindow", new NativeFunctionInfo(L"OpenWindow", 6));
			add(L"CloseWindow", new NativeFunctionInfo(L"CloseWindow", 7));
		}

	}
}
