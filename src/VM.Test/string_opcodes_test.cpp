#include "string_opcodes_test.h"

using namespace elsa;
using namespace elsa::vm;

int string_opcodes_test() { return 0; };

class StringOpCodesTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		program_.add_func(std::make_unique<FunctionInfo>(L"main", 0, 1, ep, FunctionType::Static));
		program_.add_string(std::make_unique<StringInfo>(L"Hello World!"));
		program_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(StringOpCodesTest, SCONST)
{
	program_.emit(
	{
		sconst, 0,
		s_local, 0,

		// H
		l_local, 0,
		l_ele, 0,
		halt,

		// l
		l_local, 0,
		l_ele, 3,
		halt,

		// space
		l_local, 0,
		l_ele, 5,
		halt,

		// W
		l_local, 0,
		l_ele, 6,
		halt,

		// !
		l_local, 0,
		l_ele, 11,
	});

	auto vm = VM(program_);

	vm.execute();

	ASSERT_EQ(L'H', vm.eval_stack_top().c());

	vm.execute();

	ASSERT_EQ(L'l', vm.eval_stack_top().c());

	vm.execute();

	ASSERT_EQ(L' ', vm.eval_stack_top().c());

	vm.execute();

	ASSERT_EQ(L'W', vm.eval_stack_top().c());

	vm.execute();

	ASSERT_EQ(L'!', vm.eval_stack_top().c());
}