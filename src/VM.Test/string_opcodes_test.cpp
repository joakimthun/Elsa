#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

class StringOpCodesTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		vm_.add_constant_entry(new FunctionInfo("main", 0, 1, ep, FunctionType::Static));
		vm_.add_constant_entry(new StringEntry(L"Hello World!"));
		vm_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(StringOpCodesTest, SCONST)
{
	std::vector<int> p =
	{
		sconst, 1,
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
	};

	vm_.set_program(p);

	vm_.execute();

	EXPECT_EQ('H', vm_.eval_stack_top().c());

	vm_.execute();

	EXPECT_EQ('l', vm_.eval_stack_top().c());

	vm_.execute();

	EXPECT_EQ(' ', vm_.eval_stack_top().c());

	vm_.execute();

	EXPECT_EQ('W', vm_.eval_stack_top().c());

	vm_.execute();

	EXPECT_EQ('!', vm_.eval_stack_top().c());
}