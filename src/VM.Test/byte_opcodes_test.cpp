#include "int_opcodes_test.h"

using namespace elsa;
using namespace elsa::vm;

int byte_opcodes_test() { return 0; };

class ByteOpCodesTest : public testing::Test {
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

TEST_F(ByteOpCodesTest, ICONST)
{
	program_.emit(
	{
		bconst, 6
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(6, vm.eval_stack_top().b());
}

TEST_F(ByteOpCodesTest, BADD)
{
	program_.emit(
	{
		bconst, 6,
		bconst, 6,
		badd
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(12, vm.eval_stack_top().b());
}

TEST_F(ByteOpCodesTest, BMUL)
{
	program_.emit(
	{
		bconst, 6,
		bconst, 6,
		bmul
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(36, vm.eval_stack_top().b());
}

TEST_F(ByteOpCodesTest, BSUB)
{
	program_.emit(
	{
		bconst, 6,
		bconst, 6,
		bsub
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(0, vm.eval_stack_top().b());
}

TEST_F(ByteOpCodesTest, BDIV)
{
	program_.emit(
	{
		bconst, 12,
		bconst, 4,
		bdiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(3, vm.eval_stack_top().b());
}

TEST_F(ByteOpCodesTest, BDIV_SAME_VALUE)
{
	program_.emit(
	{
		bconst, 10,
		bconst, 10,
		bdiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(1, vm.eval_stack_top().b());
}

TEST_F(ByteOpCodesTest, BDIV_GT)
{
	program_.emit(
	{
		bconst, 14,
		bconst, 16,
		bdiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(0, vm.eval_stack_top().b());
}

TEST_F(ByteOpCodesTest, BR_BEQ_JUMP)
{
	program_.emit(
	{
		bconst, 6,
		bconst, 6,
		br_beq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(ByteOpCodesTest, BR_BEQ_NO_JUMP)
{

	program_.emit(
	{
		bconst, 8,
		bconst, 6,
		br_beq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(ByteOpCodesTest, BR_BNEQ_JUMP)
{
	program_.emit(
	{
		bconst, 1,
		bconst, 2,
		br_bneq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(ByteOpCodesTest, BR_BNEQ_NO_JUMP)
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

TEST_F(ByteOpCodesTest, BEQ_TRUE)
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

	EXPECT_EQ(1, vm.eval_stack_top().i());
}

TEST_F(ByteOpCodesTest, BEQ_FALSE)
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

	EXPECT_EQ(0, vm.eval_stack_top().i());
}

TEST_F(ByteOpCodesTest, BNEQ_TRUE)
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

	EXPECT_EQ(1, vm.eval_stack_top().i());
}

TEST_F(ByteOpCodesTest, BNEQ_FALSE)
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

	EXPECT_EQ(0, vm.eval_stack_top().i());
}

TEST_F(ByteOpCodesTest, BLT)
{
	program_.emit(
	{
		bconst, 5,
		bconst, 10,
		blt,
		halt,
		bconst, 10,
		bconst, 5,
		blt,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(1, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(0, vm.eval_stack_top().i());
}

TEST_F(ByteOpCodesTest, BGT)
{
	program_.emit(
	{
		bconst, 5,
		bconst, 10,
		bgt,
		halt,
		bconst, 10,
		bconst, 5,
		bgt,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(0, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(1, vm.eval_stack_top().i());
}

TEST_F(ByteOpCodesTest, BOR)
{
	program_.emit(
	{
		bconst, 0,
		bconst, 0,
		bor,
		halt,
		bconst, 1,
		bconst, 0,
		bor,
		halt,
		bconst, 1,
		bconst, 1,
		bor,
		halt,
	});

	auto vm = VM(program_);

	vm.execute();
	EXPECT_EQ(0, vm.eval_stack_top().b());

	vm.execute();
	EXPECT_EQ(1, vm.eval_stack_top().b());

	vm.execute();
	EXPECT_EQ(1, vm.eval_stack_top().b());
}

TEST_F(ByteOpCodesTest, BAND)
{
	program_.emit(
	{
		bconst, 0,
		bconst, 0,
		band,
		halt,
		bconst, 1,
		bconst, 0,
		band,
		halt,
		bconst, 1,
		bconst, 1,
		band,
		halt,
	});

	auto vm = VM(program_);

	vm.execute();
	EXPECT_EQ(0, vm.eval_stack_top().b());

	vm.execute();
	EXPECT_EQ(0, vm.eval_stack_top().b());

	vm.execute();
	EXPECT_EQ(1, vm.eval_stack_top().b());
}