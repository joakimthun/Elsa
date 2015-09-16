#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

TEST(CONST, LOAD_INT)
{
	std::vector<int> p =
	{
		iconst, 10,
	};

	auto vm = VM(p);
	int ep = 0;

	vm.add_constant_entry(new FunctionInfo("main", 0, 1, ep, FunctionType::Static));
	vm.set_entry_point(ep);
	vm.execute();

	EXPECT_EQ(10, vm.eval_stack_top().i());
}
