#include "int_opcodes_test.h"

using namespace elsa;
using namespace elsa::vm;

int int_opcodes_test() { return 0; };

class IntOpCodesTest : public testing::Test {
protected:
	virtual void SetUp() 
	{
		int ep = 0;

		program_.add_func(std::make_unique<FunctionInfo>(L"main", 0, 0, ep, FunctionType::Static));
		program_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(IntOpCodesTest, ICONST)
{
	program_.emit(
	{
		iconst, 6
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(6, vm.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IADD)
{
	program_.emit(
	{
		iconst, 6,
		iconst, 6,
		iadd
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(12, vm.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IMUL)
{
	program_.emit(
	{
		iconst, 6,
		iconst, 6,
		imul
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(36, vm.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, ISUB)
{
	program_.emit(
	{
		iconst, 6,
		iconst, 6,
		isub
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(0, vm.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, ISUB_NEG_VALUE)
{
	program_.emit(
	{
		iconst, 40,
		iconst, 45,
		isub
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(-5, vm.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IDIV)
{
	program_.emit(
	{
		iconst, 12,
		iconst, 4,
		idiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(3, vm.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IDIV_SAME_VALUE)
{
	program_.emit(
	{
		iconst, 10,
		iconst, 10,
		idiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(1, vm.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IDIV_GT)
{
	program_.emit(
	{
		iconst, 14,
		iconst, 16,
		idiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(0, vm.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, BR_IEQ_JUMP)
{
	program_.emit(
	{
		iconst, 6,
		iconst, 6,
		br_ieq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(IntOpCodesTest, BR_IEQ_NO_JUMP)
{

	program_.emit(
	{
		iconst, 8,
		iconst, 6,
		br_ieq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(IntOpCodesTest, BR_INEQ_JUMP)
{
	program_.emit(
	{
		iconst, 1,
		iconst, 2,
		br_ineq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(IntOpCodesTest, BR_INEQ_NO_JUMP)
{

	program_.emit(
	{
		iconst, 1,
		iconst, 1,
		br_ineq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(IntOpCodesTest, IEQ_TRUE)
{
	program_.emit(
	{
		iconst, 1,
		iconst, 1,
		ieq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(IntOpCodesTest, IEQ_FALSE)
{
	program_.emit(
	{
		iconst, 1,
		iconst, 0,
		ieq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}

TEST_F(IntOpCodesTest, INEQ_TRUE)
{
	program_.emit(
	{
		iconst, 1,
		iconst, 0,
		ineq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(IntOpCodesTest, INEQ_FALSE)
{
	program_.emit(
	{
		iconst, 0,
		iconst, 0,
		ineq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}