#include "native_function_table.h"

namespace elsa {
	namespace compiler {

		NativeFunctionTable::NativeFunctionTable()
		{
			initialize();
		}

		void NativeFunctionTable::initialize()
		{
			auto print = new NativeFunctionInfo(L"Print", ObjectType::Void, 0);
			print->add_arg(new ElsaType(ObjectType::Object));

			add(L"Print", print);

			auto println = new NativeFunctionInfo(L"PrintLn", ObjectType::Void, 1);
			print->add_arg(new ElsaType(ObjectType::Object));

			add(L"PrintLn", println);
		}

	}
}
