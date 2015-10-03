#include "int_opcodes_test.h"

using namespace elsa;
using namespace elsa::vm;

int int_opcodes_test() { return 0; };

class IntOpCodesTest : public testing::Test {
protected:
	virtual void SetUp() 
	{
		int ep = 0;

		vm_.constant_pool().add_func(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
		vm_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(IntOpCodesTest, ICONST)
{
	std::vector<int> p =
	{
		iconst, 6
	};

	vm_.set_program(p);

	vm_.execute();

	EXPECT_EQ(6, vm_.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IADD)
{
	std::vector<int> p =
	{
		iconst, 6,
		iconst, 6,
		iadd
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(12, vm_.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IMUL)
{
	std::vector<int> p =
	{
		iconst, 6,
		iconst, 6,
		imul
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(36, vm_.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, ISUB)
{
	std::vector<int> p =
	{
		iconst, 6,
		iconst, 6,
		isub
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(0, vm_.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, ISUB_NEG_VALUE)
{

	std::vector<int> p =
	{
		iconst, 40,
		iconst, 45,
		isub
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(-5, vm_.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IDIV)
{
	std::vector<int> p =
	{
		iconst, 12,
		iconst, 4,
		idiv
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(3, vm_.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IDIV_SAME_VALUE)
{
	std::vector<int> p =
	{
		iconst, 10,
		iconst, 10,
		idiv
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(1, vm_.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, IDIV_GT)
{
	std::vector<int> p =
	{
		iconst, 14,
		iconst, 16,
		idiv
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(0, vm_.eval_stack_top().i());
}

TEST_F(IntOpCodesTest, BR_IEQ_JUMP)
{
	std::vector<int> p =
	{
		iconst, 6,
		iconst, 6,
		br_ieq, 10,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_EQ(10, vm_.get_pc());
}

TEST_F(IntOpCodesTest, BR_IEQ_NO_JUMP)
{

	std::vector<int> p =
	{
		iconst, 8,
		iconst, 6,
		br_ieq, 0,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_NE(0, vm_.get_pc());
}

TEST_F(IntOpCodesTest, BR_INEQ_JUMP)
{
	std::vector<int> p =
	{
		iconst, 1,
		iconst, 2,
		br_ineq, 10,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_EQ(10, vm_.get_pc());
}

TEST_F(IntOpCodesTest, BR_INEQ_NO_JUMP)
{

	std::vector<int> p =
	{
		iconst, 1,
		iconst, 1,
		br_ineq, 0,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_NE(0, vm_.get_pc());
}

TEST_F(IntOpCodesTest, IEQ_TRUE)
{
	std::vector<int> p =
	{
		iconst, 1,
		iconst, 1,
		ieq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(IntOpCodesTest, IEQ_FALSE)
{
	std::vector<int> p =
	{
		iconst, 1,
		iconst, 0,
		ieq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}

TEST_F(IntOpCodesTest, INEQ_TRUE)
{
	std::vector<int> p =
	{
		iconst, 1,
		iconst, 0,
		ineq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(IntOpCodesTest, INEQ_FALSE)
{
	std::vector<int> p =
	{
		iconst, 0,
		iconst, 0,
		ineq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}