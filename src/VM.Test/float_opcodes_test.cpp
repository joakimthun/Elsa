#include "float_opcodes_test.h"

using namespace elsa;
using namespace elsa::vm;

int float_opcodes_test() { return 0; };

class FloatOpCodesTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		program_.add_func(new FunctionInfo(L"main", 0, 0, ep, FunctionType::Static));
		program_.add_float(new FloatInfo(10.1f)); // index: 0
		program_.add_float(new FloatInfo(20.2f)); // index: 1
		program_.add_float(new FloatInfo(30.3f)); // index: 2
		program_.add_float(new FloatInfo(40.4f)); // index: 3
		program_.add_float(new FloatInfo(50.5f)); // index: 4
		program_.add_float(new FloatInfo(-10.6f)); // index: 5

		program_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(FloatOpCodesTest, FCONST)
{
	program_.emit(
	{
		fconst, 1
	});

	auto vm = VM(program_);

	vm.execute();

	EXPECT_FLOAT_EQ(20.2f, vm.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FADD)
{
	program_.emit(
	{
		fconst, 1,
		fconst, 2,
		fadd
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_FLOAT_EQ(50.5f, vm.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FMUL)
{
	program_.emit(
	{
		fconst, 1,
		fconst, 2,
		fmul
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_FLOAT_EQ(612.06f, vm.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FSUB)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 0,
		fsub
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_FLOAT_EQ(0.f, vm.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FSUB_NEG_VALUE)
{
	program_.emit(
	{
		fconst, 2,
		fconst, 3,
		fsub
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_FLOAT_EQ(-10.1f, vm.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FDIV)
{
	program_.emit(
	{
		fconst, 3,
		fconst, 1,
		fdiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_FLOAT_EQ(2.f, vm.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FDIV_SAME_VALUE)
{
	program_.emit(
	{
		fconst, 1,
		fconst, 1,
		fdiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_FLOAT_EQ(1, vm.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FDIV_GT)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 3,
		fdiv
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_FLOAT_EQ(0.25f, vm.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, BR_FEQ_JUMP)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 0,
		br_feq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(FloatOpCodesTest, BR_FEQ_NO_JUMP)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 1,
		br_feq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(FloatOpCodesTest, BR_FNEQ_JUMP)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 1,
		br_fneq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(FloatOpCodesTest, BR_FNEQ_NO_JUMP)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 0,
		br_fneq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(FloatOpCodesTest, FEQ_TRUE)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 0,
		feq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(FloatOpCodesTest, FEQ_FALSE)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 1,
		feq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}

TEST_F(FloatOpCodesTest, FNEQ_TRUE)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 1,
		fneq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(FloatOpCodesTest, FNEQ_FALSE)
{
	program_.emit(
	{
		fconst, 0,
		fconst, 0,
		fneq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}