#include "locals_test.h"

using namespace elsa;
using namespace elsa::vm;

int locals_test() { return 0; };

TEST(LOCALS, STORE_LOAD_INT)
{
	VMProgram program_;

	program_.emit(
	{
		iconst, 10,
		s_local, 0,
		l_local, 0,
		halt
	});

	int ep = 0;

	program_.add_func(new FunctionInfo("main", 0, 1, ep, FunctionType::Static));
	program_.set_entry_point(ep);

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(10, vm.eval_stack_top().i());
}
