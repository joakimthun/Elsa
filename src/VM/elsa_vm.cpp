#include <iostream>
#include <vector>

#include "vm.h"
#include "opcodes.h"
#include "constants\function_entry.h"

using namespace elsa::vm;

void print_rec(int value);

VM* recursive_print();
VM* simple_call_static();
VM* simple_ret_and_print();
VM* simple_ret_added_args_and_print();

int main()
{
	VM* vm = simple_ret_added_args_and_print();
	
	vm->execute();

	delete vm;

	print_rec(10);

	return 0;
}

void print_rec(int value)
{
	std::cout << value << std::endl;

	if (value == 0)
	{
		return;
	}

	print_rec(value - 1);
}

VM* recursive_print()
{
	std::vector<int> p =
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

	int ep = 7;

	auto vm = new VM(p);

	vm->add_constant_entry(new FunctionEntry("main", 0, 0, ep, FunctionType::Static));
	vm->add_constant_entry(new FunctionEntry("print", 0, 0, 0, FunctionType::Static));
	vm->set_entry_point(ep);

	return vm;
}

VM* simple_call_static()
{
	std::vector<int> p =
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
	
	int ep = 7;
	
	auto vm = new VM(p);
	
	vm->add_constant_entry(new FunctionEntry("main", 0, 0, ep, FunctionType::Static));
	vm->add_constant_entry(new FunctionEntry("print", 0, 0, 0, FunctionType::Static));
	vm->set_entry_point(ep);

	return vm;
}

VM* simple_ret_and_print()
{
	std::vector<int> p =
	{
		// Print
		iconst, 2,
		iconst, 6,
		iadd,
		ret,
		// Main
		call_static, 0,
		print_ln,
		halt
	};

	int ep = 6;

	VM* vm = new VM(p);

	vm->add_constant_entry(new FunctionEntry("main", 0, 0, ep, FunctionType::Static));
	vm->add_constant_entry(new FunctionEntry("ret_int", 0, 0, 0, FunctionType::Static));
	vm->set_entry_point(ep);

	return vm;
}

VM* simple_ret_added_args_and_print()
{
	std::vector<int> p =
	{
		load_arg, 0,
		load_arg, 1,
		iadd,
		ret,
		// Main
		iconst, 12,
		iconst, 5,
		call_static, 0,
		print_ln,
		halt
	};

	int ep = 6;

	VM* vm = new VM(p);

	vm->add_constant_entry(new FunctionEntry("main", 0, 0, ep, FunctionType::Static));
	vm->add_constant_entry(new FunctionEntry("ret_added", 2, 0, 0, FunctionType::Static));
	vm->set_entry_point(ep);

	return vm;
}
