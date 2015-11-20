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
			print->add_arg();
			print->add_arg_type(0, ObjectType::Int);
			print->add_arg_type(0, ObjectType::Bool);
			print->add_arg_type(0, ObjectType::Char);
			print->add_arg_type(0, ObjectType::Float);

			add(L"Print", print);

			auto println = new NativeFunctionInfo(L"PrintLn", ObjectType::Void, 1);
			println->add_arg();
			println->add_arg_type(0, ObjectType::Int);
			println->add_arg_type(0, ObjectType::Bool);
			println->add_arg_type(0, ObjectType::Char);
			println->add_arg_type(0, ObjectType::Float);

			add(L"PrintLn", println);
		}

	}
}
