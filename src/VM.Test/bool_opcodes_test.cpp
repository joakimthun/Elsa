#include "bool_opcodes_test.h"

using namespace elsa;
using namespace elsa::vm;

int bool_opcodes_test() { return 0; };

class BoolOpCodesTest : public testing::Test {
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

TEST_F(BoolOpCodesTest, BCONST_TRUE)
{
	std::vector<int> p =
	{
		bconst, 1
	};

	vm_.set_program(p);

	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(BoolOpCodesTest, BCONST_FALSE)
{
	std::vector<int> p =
	{
		bconst, 0
	};

	vm_.set_program(p);

	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}


TEST_F(BoolOpCodesTest, BR_BEQ_JUMP)
{
	std::vector<int> p =
	{
		bconst, 1,
		bconst, 1,
		br_beq, 10,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_EQ(10, vm_.get_pc());
}

TEST_F(BoolOpCodesTest, BR_BEQ_NO_JUMP)
{
	std::vector<int> p =
	{
		bconst, 1,
		bconst, 0,
		br_beq, 0,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_NE(0, vm_.get_pc());
}

TEST_F(BoolOpCodesTest, BR_BNEQ_JUMP)
{
	std::vector<int> p =
	{
		bconst, 1,
		bconst, 0,
		br_bneq, 10,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_EQ(10, vm_.get_pc());
}

TEST_F(BoolOpCodesTest, BR_BNEQ_NO_JUMP)
{
	std::vector<int> p =
	{
		bconst, 1,
		bconst, 1,
		br_bneq, 0,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_NE(0, vm_.get_pc());
}

TEST_F(BoolOpCodesTest, BEQ_TRUE)
{
	std::vector<int> p =
	{
		bconst, 1,
		bconst, 1,
		beq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(BoolOpCodesTest, BEQ_FALSE)
{
	std::vector<int> p =
	{
		bconst, 1,
		bconst, 0,
		beq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}

TEST_F(BoolOpCodesTest, BNEQ_TRUE)
{
	std::vector<int> p =
	{
		bconst, 1,
		bconst, 0,
		bneq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(BoolOpCodesTest, BNEQ_FALSE)
{
	std::vector<int> p =
	{
		bconst, 0,
		bconst, 0,
		bneq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}