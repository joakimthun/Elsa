#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa;
using namespace elsa::vm;

TEST(LOCALS, STORE_LOAD_INT)
{
	std::vector<int> p =
	{
		iconst, 10,
		s_local, 0,
		l_local, 0,
		halt
	};

	auto vm = VM(p);
	int ep = 0;

	vm.constant_pool().add_func(new FunctionInfo("main", 0, 1, ep, FunctionType::Static));
	vm.set_entry_point(ep);
	vm.execute();

	EXPECT_EQ(10, vm.eval_stack_top().i());
}
