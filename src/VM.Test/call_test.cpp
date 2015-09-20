#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

TEST(STATIC_CALL, RETURN_INT)
{
	std::vector<int> p =
	{
		iconst, 6,
		ret,

		// Main
		call, 0,
		halt
	};

	int ep = 3;

	auto vm = VM(p);

	vm.add_constant_entry(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
	vm.add_constant_entry(new FunctionInfo("print", 0, 0, 0, FunctionType::Static));
	vm.set_entry_point(ep);

	vm.execute();

	EXPECT_EQ(6, vm.eval_stack_top().i());
}
