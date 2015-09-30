#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

class RecursiveFactorialTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 20;

		vm_.constant_pool().add_func(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
		vm_.constant_pool().add_func(new FunctionInfo("factorial", 1, 0, 0, FunctionType::Static));
		vm_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	void set_fact_arg(int arg)
	{
		std::vector<int> p =
		{
			// factorial
			iconst, 1,
			l_arg, 0,
			br_ineq, 9,
			iconst, 1,
			ret,
			l_arg, 0,
			l_arg, 0,
			iconst, 1,
			isub,
			call, 0,
			imul,
			ret,

			// main
			iconst, arg,
			call, 0,
			halt
		};

		vm_.set_program(p);
	}

	VM vm_;
};

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_1)
{
	set_fact_arg(1);
	vm_.execute();

	EXPECT_EQ(1, vm_.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_2)
{
	set_fact_arg(2);
	vm_.execute();

	EXPECT_EQ(2, vm_.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_3)
{
	set_fact_arg(3);
	vm_.execute();

	EXPECT_EQ(6, vm_.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_4)
{
	set_fact_arg(4);
	vm_.execute();

	EXPECT_EQ(24, vm_.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_5)
{
	set_fact_arg(5);
	vm_.execute();

	EXPECT_EQ(120, vm_.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_6)
{
	set_fact_arg(6);
	vm_.execute();

	EXPECT_EQ(720, vm_.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_10)
{
	set_fact_arg(10);
	vm_.execute();

	EXPECT_EQ(3628800, vm_.eval_stack_top().i());
}
