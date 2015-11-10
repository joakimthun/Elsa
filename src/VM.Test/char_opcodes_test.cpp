#include "char_opcodes_test.h"

using namespace elsa;
using namespace elsa::vm;

int char_opcodes_test() { return 0; };

class CharOpCodesTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		program_.add_func(std::make_unique<FunctionInfo>(L"main", 0, 0, ep, FunctionType::Static));
		program_.add_char(std::make_unique<CharInfo>('a'));
		program_.add_char(std::make_unique<CharInfo>('b'));
		program_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(CharOpCodesTest, CCONST)
{
	program_.emit(
	{
		cconst, 0
	});

	auto vm = VM(program_);

	vm.execute();

	EXPECT_EQ('a', vm.eval_stack_top().c());
}

TEST_F(CharOpCodesTest, BR_CEQ_JUMP)
{
	program_.emit(
	{
		cconst, 0,
		cconst, 0,
		br_ceq, 7,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(7, vm.get_pc());
}

TEST_F(CharOpCodesTest, BR_CEQ_NO_JUMP)
{
	program_.emit(
	{
		cconst, 0,
		cconst, 1,
		br_ceq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(CharOpCodesTest, BR_CNEQ_JUMP)
{
	program_.emit(
	{
		cconst, 0,
		cconst, 1,
		br_cneq, 10,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_EQ(10, vm.get_pc());
}

TEST_F(CharOpCodesTest, BR_BNEQ_NO_JUMP)
{
	program_.emit(
	{
		cconst, 0,
		cconst, 0,
		br_cneq, 0,
		halt
	});

	auto vm = VM(program_);
	vm.execute_one();
	vm.execute_one();
	vm.execute_one();

	EXPECT_NE(0, vm.get_pc());
}

TEST_F(CharOpCodesTest, CEQ_TRUE)
{
	program_.emit(
	{
		cconst, 0,
		cconst, 0,
		ceq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(CharOpCodesTest, CEQ_FALSE)
{
	program_.emit(
	{
		cconst, 0,
		cconst, 1,
		ceq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}

TEST_F(CharOpCodesTest, CNEQ_TRUE)
{
	program_.emit(
	{
		cconst, 0,
		cconst, 1,
		cneq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(true, vm.eval_stack_top().b());
}

TEST_F(CharOpCodesTest, CNEQ_FALSE)
{
	program_.emit(
	{
		cconst, 0,
		cconst, 0,
		cneq,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	EXPECT_EQ(false, vm.eval_stack_top().b());
}