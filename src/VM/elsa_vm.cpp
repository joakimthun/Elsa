#include <iostream>

#include "vm.h"
#include "opcodes.h"
#include "constants\function_entry.h"

int main()
{
	using namespace elsa::vm;

	int p[]
	{
		// Print
		iconst, 2,
		iconst, 6,
		imul,
		print_ln,
		ret,
		// Main
		call_static, 0,
		halt
	};

	auto vm = VM(p, 10);

	vm.add_constant_entry(new FunctionEntry("main", 0, 0, 7, FunctionType::Static));
	vm.add_constant_entry(new FunctionEntry("print", 0, 0, 0, FunctionType::Static));
	vm.set_entry_point(7);


	vm.execute();

	return 0;
}

