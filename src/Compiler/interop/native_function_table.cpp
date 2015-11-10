#include "native_function_table.h"

namespace elsa {
	namespace compiler {

		NativeFunctionTable::NativeFunctionTable()
		{
			initialize();
		}

		void NativeFunctionTable::initialize()
		{
			auto print = new NativeFunctionInfo(L"Print", OType::Void, 0);
			print->add_arg();
			print->add_arg_type(0, OType::Int);
			print->add_arg_type(0, OType::Bool);
			print->add_arg_type(0, OType::Char);
			print->add_arg_type(0, OType::Float);

			add(L"Print", print);

			auto println = new NativeFunctionInfo(L"PrintLn", OType::Void, 1);
			println->add_arg();
			println->add_arg_type(0, OType::Int);
			println->add_arg_type(0, OType::Bool);
			println->add_arg_type(0, OType::Char);
			println->add_arg_type(0, OType::Float);

			add(L"PrintLn", println);
		}

	}
}