#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa;
using namespace elsa::vm;

class FloatOpCodesTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		vm_.constant_pool().add_func(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
		vm_.constant_pool().add_float(new FloatInfo(10.1f)); // index: 0
		vm_.constant_pool().add_float(new FloatInfo(20.2f)); // index: 1
		vm_.constant_pool().add_float(new FloatInfo(30.3f)); // index: 2
		vm_.constant_pool().add_float(new FloatInfo(40.4f)); // index: 3
		vm_.constant_pool().add_float(new FloatInfo(50.5f)); // index: 4
		vm_.constant_pool().add_float(new FloatInfo(-10.6f)); // index: 5

		vm_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(FloatOpCodesTest, FCONST)
{
	std::vector<int> p =
	{
		fconst, 1
	};

	vm_.set_program(p);

	vm_.execute();

	EXPECT_FLOAT_EQ(20.2f, vm_.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FADD)
{
	std::vector<int> p =
	{
		fconst, 1,
		fconst, 2,
		fadd
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_FLOAT_EQ(50.5f, vm_.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FMUL)
{
	std::vector<int> p =
	{
		fconst, 1,
		fconst, 2,
		fmul
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_FLOAT_EQ(612.06f, vm_.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FSUB)
{
	std::vector<int> p =
	{
		fconst, 0,
		fconst, 0,
		fsub
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_FLOAT_EQ(0.f, vm_.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FSUB_NEG_VALUE)
{

	std::vector<int> p =
	{
		fconst, 2,
		fconst, 3,
		fsub
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_FLOAT_EQ(-10.1f, vm_.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FDIV)
{
	std::vector<int> p =
	{
		fconst, 3,
		fconst, 1,
		fdiv
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_FLOAT_EQ(2.f, vm_.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FDIV_SAME_VALUE)
{
	std::vector<int> p =
	{
		fconst, 1,
		fconst, 1,
		fdiv
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_FLOAT_EQ(1, vm_.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, FDIV_GT)
{
	std::vector<int> p =
	{
		fconst, 0,
		fconst, 3,
		fdiv
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_FLOAT_EQ(0.25f, vm_.eval_stack_top().f());
}

TEST_F(FloatOpCodesTest, BR_FEQ_JUMP)
{
	std::vector<int> p =
	{
		fconst, 0,
		fconst, 0,
		br_feq, 10,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_EQ(10, vm_.get_pc());
}

TEST_F(FloatOpCodesTest, BR_FEQ_NO_JUMP)
{

	std::vector<int> p =
	{
		fconst, 0,
		fconst, 1,
		br_feq, 0,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_NE(0, vm_.get_pc());
}

TEST_F(FloatOpCodesTest, BR_FNEQ_JUMP)
{
	std::vector<int> p =
	{
		fconst, 0,
		fconst, 1,
		br_fneq, 10,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_EQ(10, vm_.get_pc());
}

TEST_F(FloatOpCodesTest, BR_FNEQ_NO_JUMP)
{

	std::vector<int> p =
	{
		fconst, 0,
		fconst, 0,
		br_fneq, 0,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_NE(0, vm_.get_pc());
}

TEST_F(FloatOpCodesTest, FEQ_TRUE)
{
	std::vector<int> p =
	{
		fconst, 0,
		fconst, 0,
		feq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(FloatOpCodesTest, FEQ_FALSE)
{
	std::vector<int> p =
	{
		fconst, 0,
		fconst, 1,
		feq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}

TEST_F(FloatOpCodesTest, FNEQ_TRUE)
{
	std::vector<int> p =
	{
		fconst, 0,
		fconst, 1,
		fneq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(FloatOpCodesTest, FNEQ_FALSE)
{
	std::vector<int> p =
	{
		fconst, 0,
		fconst, 0,
		fneq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}