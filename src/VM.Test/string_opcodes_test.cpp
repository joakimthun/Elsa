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
		iconst, 0,
		l_ele,
		halt,

		// l
		l_local, 0,
		iconst, 3,
		l_ele,
		halt,

		// space
		l_local, 0,
		iconst, 5,
		l_ele,
		halt,

		// W
		l_local, 0,
		iconst, 6,
		l_ele,
		halt,

		// !
		l_local, 0,
		iconst, 11,
		l_ele,
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