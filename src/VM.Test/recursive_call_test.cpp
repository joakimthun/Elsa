#include "recursive_call_test.h"

using namespace elsa;
using namespace elsa::vm;

int recursive_call_test() { return 0; };

class RecursiveFactorialTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 20;

		program_.add_func(new FunctionInfo(L"main", 0, 0, ep, FunctionType::Static));
		program_.add_func(new FunctionInfo(L"factorial", 1, 0, 0, FunctionType::Static));
		program_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	void set_fact_arg(int arg)
	{
		program_.emit(
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
		});
	}

	VMProgram program_;
};

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_1)
{
	set_fact_arg(1);
	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(1, vm.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_2)
{
	set_fact_arg(2);
	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(2, vm.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_3)
{
	set_fact_arg(3);
	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(6, vm.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_4)
{
	set_fact_arg(4);
	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(24, vm.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_5)
{
	set_fact_arg(5);
	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(120, vm.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_6)
{
	set_fact_arg(6);
	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(720, vm.eval_stack_top().i());
}

TEST_F(RecursiveFactorialTest, RECURSIVE_FACTORIAL_10)
{
	set_fact_arg(10);
	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(3628800, vm.eval_stack_top().i());
}
