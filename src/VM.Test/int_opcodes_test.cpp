#include <gtest\gtest.h>

#include <memory>
#include "vm.h"

using namespace elsa::vm;

struct OpCodesSetup
{
	static inline VM* execute(std::vector<int>& p)
	{
		int ep = 0;

		auto vm = new VM(p);

		vm->add_constant_entry(new FunctionInfo("main", 0, 0, ep, FunctionType::Static));
		vm->set_entry_point(ep);

		return vm;
	};
};

TEST(OPCODES, ICONST)
{
	std::vector<int> p =
	{
		iconst, 6
	};

	auto vm = std::unique_ptr<VM>(OpCodesSetup::execute(p));
	vm->execute();

	EXPECT_EQ(6, vm->eval_stack_top().i());
}

TEST(OPCODES, IADD)
{
	std::vector<int> p =
	{
		iconst, 6,
		iconst, 6,
		iadd
	};

	auto vm = std::unique_ptr<VM>(OpCodesSetup::execute(p));
	vm->execute();

	EXPECT_EQ(12, vm->eval_stack_top().i());
}

TEST(OPCODES, IMUL)
{
	std::vector<int> p =
	{
		iconst, 6,
		iconst, 6,
		imul
	};

	auto vm = std::unique_ptr<VM>(OpCodesSetup::execute(p));
	vm->execute();

	EXPECT_EQ(36, vm->eval_stack_top().i());
}

TEST(OPCODES, ISUB)
{
	std::vector<int> p1 =
	{
		iconst, 6,
		iconst, 6,
		isub
	};

	auto vm1 = std::unique_ptr<VM>(OpCodesSetup::execute(p1));
	vm1->execute();

	EXPECT_EQ(0, vm1->eval_stack_top().i());

	std::vector<int> p2 =
	{
		iconst, 40,
		iconst, 45,
		isub
	};

	auto vm2 = std::unique_ptr<VM>(OpCodesSetup::execute(p2));
	vm2->execute();

	EXPECT_EQ(-5, vm2->eval_stack_top().i());
}

TEST(OPCODES, IDIV)
{
	std::vector<int> p1 =
	{
		iconst, 12,
		iconst, 4,
		idiv
	};

	auto vm1 = std::unique_ptr<VM>(OpCodesSetup::execute(p1));
	vm1->execute();

	EXPECT_EQ(3, vm1->eval_stack_top().i());

	std::vector<int> p2 =
	{
		iconst, 10,
		iconst, 10,
		idiv
	};

	auto vm2 = std::unique_ptr<VM>(OpCodesSetup::execute(p2));
	vm2->execute();

	EXPECT_EQ(1, vm2->eval_stack_top().i());

	std::vector<int> p3 =
	{
		iconst, 14,
		iconst, 16,
		idiv
	};

	auto vm3 = std::unique_ptr<VM>(OpCodesSetup::execute(p2));
	vm3->execute();

	EXPECT_EQ(1, vm3->eval_stack_top().i());
}

TEST(OPCODES, BR_IEQ)
{
	std::vector<int> p1 =
	{
		iconst, 6,
		iconst, 6,
		br_ieq, 6,
		halt
	};

	auto vm1 = std::unique_ptr<VM>(OpCodesSetup::execute(p1));
	vm1->execute_one();
	vm1->execute_one();
	vm1->execute_one();

	EXPECT_EQ(6, vm1->get_pc());

	std::vector<int> p2 =
	{
		iconst, 8,
		iconst, 6,
		br_ieq, 0,
		halt
	};

	auto vm2 = std::unique_ptr<VM>(OpCodesSetup::execute(p2));
	vm2->execute_one();
	vm2->execute_one();
	vm2->execute_one();

	EXPECT_NE(0, vm2->get_pc());
}
