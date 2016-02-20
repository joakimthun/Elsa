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
			add(L"CreateWindowHandle", new NativeFunctionInfo(L"CreateWindowHandle", 5));
			add(L"OpenWindowHandle", new NativeFunctionInfo(L"OpenWindowHandle", 6));
			add(L"CloseWindowHandle", new NativeFunctionInfo(L"CloseWindowHandle", 7));
			add(L"UpdateWindowHandle", new NativeFunctionInfo(L"UpdateWindowHandle", 8));
			add(L"FillRect", new NativeFunctionInfo(L"FillRect", 9));
			add(L"Sleep", new NativeFunctionInfo(L"Sleep", 10));
			add(L"GetTicks", new NativeFunctionInfo(L"GetTicks", 11));
			add(L"KeyDown", new NativeFunctionInfo(L"KeyDown", 12));
		}

	}
}
