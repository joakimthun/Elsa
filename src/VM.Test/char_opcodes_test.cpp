#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

class CharOpCodesTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		vm_.constant_pool().add_func(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
		vm_.constant_pool().add_char(new CharInfo('a'));
		vm_.constant_pool().add_char(new CharInfo('b'));
		vm_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(CharOpCodesTest, CCONST)
{
	std::vector<int> p =
	{
		cconst, 0
	};

	vm_.set_program(p);

	vm_.execute();

	EXPECT_EQ('a', vm_.eval_stack_top().c());
}

TEST_F(CharOpCodesTest, BR_CEQ_JUMP)
{
	std::vector<int> p =
	{
		cconst, 0,
		cconst, 0,
		br_ceq, 7,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_EQ(7, vm_.get_pc());
}

TEST_F(CharOpCodesTest, BR_CEQ_NO_JUMP)
{
	std::vector<int> p =
	{
		cconst, 0,
		cconst, 1,
		br_ceq, 0,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_NE(0, vm_.get_pc());
}

TEST_F(CharOpCodesTest, BR_CNEQ_JUMP)
{
	std::vector<int> p =
	{
		cconst, 0,
		cconst, 1,
		br_cneq, 10,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_EQ(10, vm_.get_pc());
}

TEST_F(CharOpCodesTest, BR_BNEQ_NO_JUMP)
{
	std::vector<int> p =
	{
		cconst, 0,
		cconst, 0,
		br_cneq, 0,
		halt
	};

	vm_.set_program(p);
	vm_.execute_one();
	vm_.execute_one();
	vm_.execute_one();

	EXPECT_NE(0, vm_.get_pc());
}

TEST_F(CharOpCodesTest, CEQ_TRUE)
{
	std::vector<int> p =
	{
		cconst, 0,
		cconst, 0,
		ceq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(CharOpCodesTest, CEQ_FALSE)
{
	std::vector<int> p =
	{
		cconst, 0,
		cconst, 1,
		ceq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}

TEST_F(CharOpCodesTest, CNEQ_TRUE)
{
	std::vector<int> p =
	{
		cconst, 0,
		cconst, 1,
		cneq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(true, vm_.eval_stack_top().b());
}

TEST_F(CharOpCodesTest, CNEQ_FALSE)
{
	std::vector<int> p =
	{
		cconst, 0,
		cconst, 0,
		cneq,
		halt
	};

	vm_.set_program(p);
	vm_.execute();

	EXPECT_EQ(false, vm_.eval_stack_top().b());
}