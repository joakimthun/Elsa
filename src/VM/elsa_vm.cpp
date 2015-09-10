#include <iostream>
#include <vector>

#include "vm.h"
#include "opcodes.h"
#include "constants\function_entry.h"

void simple_call_static(std::vector<int>&, int&);
void simple_ret_and_print(std::vector<int>&, int&);
void simple_ret_added_args_and_print(std::vector<int>&, int&);

using namespace elsa::vm;

int main()
{
	std::vector<int> p;
	int ep;
	simple_ret_added_args_and_print(p, ep);

	auto vm = VM(&p.front(), p.size());

	vm.add_constant_entry(new FunctionEntry("main", 0, 0, ep, FunctionType::Static));
	//vm.add_constant_entry(new FunctionEntry("print", 0, 0, 0, FunctionType::Static));
	//vm.add_constant_entry(new FunctionEntry("ret_int", 0, 0, 0, FunctionType::Static));
	vm.add_constant_entry(new FunctionEntry("ret_added", 2, 0, 0, FunctionType::Static));
	vm.set_entry_point(ep);


	vm.execute();

	return 0;
}

void simple_call_static(std::vector<int>& p, int& ep)
{
	ep = 7;

	p =
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
}

void simple_ret_and_print(std::vector<int>& p, int& ep)
{
	ep = 6;

	p =
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
}

void simple_ret_added_args_and_print(std::vector<int>& p, int& ep)
{
	ep = 6;

	p =
	{
		arg, 0,
		arg, 1,
		iadd,
		ret,
		// Main
		iconst, 5,
		iconst, 5,
		call_static, 0,
		print_ln,
		halt
	};
}
