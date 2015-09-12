#include <iostream>
#include <vector>
#include <stdlib.h>

#include "vm.h"
#include "opcodes.h"
#include "constants\function_info.h"

using namespace elsa::vm;

void print_rec(int value);

VM* recursive_print();
VM* store_load_local();
VM* simple_call_static();
VM* simple_ret_and_print();
VM* simple_ret_added_args_and_print();

int main()
{
	VM* vm = recursive_print();
	
	vm->execute();

	//std::cout << "sizeof(bool): " << sizeof(bool) << std::endl;

	//void* ptr = malloc(sizeof(int));
	//*(int*)ptr = 10;
	//std::cout << "iptr: " << *(int*)ptr << std::endl;

	delete vm;

	//print_rec(10);

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
		l_arg, 0,
		print_ln,
		l_arg, 0,
		iconst, 0,
		b_ineq, 10, 
		ret,
		l_arg, 0,
		iconst, 1,
		isub,
		call_static, 0,
		ret,

		// Main
		iconst, 10,
		call_static, 0,
		halt
	};

	int ep = 18;

	auto vm = new VM(p);

	vm->add_constant_entry(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
	vm->add_constant_entry(new FunctionInfo("rec_print", 1, 0, 0, FunctionType::Static));
	vm->set_entry_point(ep);

	return vm;
}

VM* store_load_local()
{
	std::vector<int> p =
	{
		iconst, 10,
		s_local, 0,
		l_local, 0,
		print_ln,
		halt
	};

	int ep = 0;

	auto vm = new VM(p);

	vm->add_constant_entry(new FunctionInfo("main", 0, 1, ep, FunctionType::Static));
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
	
	vm->add_constant_entry(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
	vm->add_constant_entry(new FunctionInfo("print", 0, 0, 0, FunctionType::Static));
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

	vm->add_constant_entry(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
	vm->add_constant_entry(new FunctionInfo("ret_int", 0, 0, 0, FunctionType::Static));
	vm->set_entry_point(ep);

	return vm;
}

VM* simple_ret_added_args_and_print()
{
	std::vector<int> p =
	{
		l_arg, 0,
		l_arg, 1,
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

	vm->add_constant_entry(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
	vm->add_constant_entry(new FunctionInfo("ret_added", 2, 0, 0, FunctionType::Static));
	vm->set_entry_point(ep);

	return vm;
}
