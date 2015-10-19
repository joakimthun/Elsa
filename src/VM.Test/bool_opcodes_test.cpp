#include "bool_opcodes_test.h"

using namespace elsa;
using namespace elsa::vm;

int bool_opcodes_test() { return 0; };

class BoolOpCodesTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		program_.add_func(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
		program_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(BoolOpCodesTest, BCONST_TRUE)
{
	program_.emit(
	{
		bconst, 1
	});

	auto vm = VM(program_);

	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(BoolOpCodesTest, BCONST_FALSE)
{
	program_.emit(
	{
		bconst, 0
	});

	auto vm = VM(program_);

	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}


TEST_F(BoolOpCodesTest, BR_BEQ_JUMP)
{
	program_.emit(
	{
		bconst, 1,
		bconst, 1,
		br_beq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(BoolOpCodesTest, BR_BEQ_NO_JUMP)
{
	program_.emit(
	{
		bconst, 1,
		bconst, 0,
		br_beq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(BoolOpCodesTest, BR_BNEQ_JUMP)
{
	program_.emit(
	{
		bconst, 1,
		bconst, 0,
		br_bneq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(BoolOpCodesTest, BR_BNEQ_NO_JUMP)
{
	program_.emit(
	{
		bconst, 1,
		bconst, 1,
		br_bneq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(BoolOpCodesTest, BEQ_TRUE)
{
	program_.emit(
	{
		bconst, 1,
		bconst, 1,
		beq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(BoolOpCodesTest, BEQ_FALSE)
{
	program_.emit(
	{
		bconst, 1,
		bconst, 0,
		beq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}

TEST_F(BoolOpCodesTest, BNEQ_TRUE)
{
	program_.emit(
	{
		bconst, 1,
		bconst, 0,
		bneq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(BoolOpCodesTest, BNEQ_FALSE)
{
	program_.emit(
	{
		bconst, 0,
		bconst, 0,
		bneq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}