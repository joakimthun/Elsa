#include "call_test.h"

using namespace elsa;
using namespace elsa::vm;

int call_test() { return 0; };

TEST(STATIC_CALL, RETURN_INT)
{
	VMProgram program;

	program.emit(
	{
		iconst, 6,
		ret,

		// Main
		call, 0,
		halt
	});

	int ep = 3;

	program.add_func(std::make_unique<FunctionInfo>(L"main", 0, 0, ep, FunctionType::Static));
	program.add_func(std::make_unique<FunctionInfo>(L"print", 0, 0, 0, FunctionType::Static));
	program.set_entry_point(ep);

	auto vm = VM(program);

	vm.execute();

	EXPECT_EQ(6, vm.eval_stack_top().i());
}
