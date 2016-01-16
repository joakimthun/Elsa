#include "are_eq_test.h"

using namespace elsa;
using namespace elsa::vm;

int are_eq_test() { return 0; };

class AreEqTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		program_.add_func(std::make_unique<FunctionInfo>(L"main", 0, 10, ep, FunctionType::Static));
		program_.add_float(std::make_unique<FloatInfo>(12.0f));
		program_.add_float(std::make_unique<FloatInfo>(-99.0f));
		program_.add_char(std::make_unique<CharInfo>('a'));
		program_.add_char(std::make_unique<CharInfo>('b'));

		program_.set_entry_point(ep);

		auto si = std::make_unique<StructInfo>(L"my_struct");
		si->add_field(std::make_unique<FieldInfo>(L"field0", elsa::VMType::GCOPtr));
		si->add_field(std::make_unique<FieldInfo>(L"field1", elsa::VMType::GCOPtr));
		si->add_field(std::make_unique<FieldInfo>(L"field2", elsa::VMType::GCOPtr));
		program_.add_struct(std::move(si));

		auto si2 = std::make_unique<StructInfo>(L"my_struct2");
		si2->add_field(std::make_unique<FieldInfo>(L"field0", elsa::VMType::Int));
		program_.add_struct(std::move(si2));
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(AreEqTest, ArrayEq)
{
	program_.emit(
	{
		iconst, 3,
		new_arr, (int)VMType::Int,
		s_local, 0,
		l_local, 0,
		iconst, 10,
		ncall, 2,
		halt,
		l_local, 0,
		l_local, 0,
		ncall, 2,
		halt,
		iconst, 3,
		new_arr, (int)VMType::Int,
		s_local, 1,
		l_local, 0,
		l_local, 1,
		ncall, 2,
		halt,
	});

	auto vm = VM(program_);
	vm.execute();

	// Array instance == int -> false
	ASSERT_EQ(0, vm.eval_stack_top().i());

	// Same instance -> true
	vm.execute();
	ASSERT_EQ(1, vm.eval_stack_top().i());

	// Different instances -> false
	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());
}

TEST_F(AreEqTest, ValueEq)
{
	program_.emit(
	{
		iconst, 1,
		iconst, 1,
		ncall, 2,
		halt,
		iconst, 1,
		iconst, 2,
		ncall, 2,
		halt,
		fconst, 0,
		fconst, 0,
		ncall, 2,
		halt,
		fconst, 0,
		fconst, 1,
		ncall, 2,
		halt,
		cconst, 0,
		cconst, 0,
		ncall, 2,
		halt,
		cconst, 0,
		cconst, 1,
		ncall, 2,
		halt,
	});

	auto vm = VM(program_);

	// Int, 1 == 1 -> true
	vm.execute();
	ASSERT_EQ(1, vm.eval_stack_top().i());

	// Int, 1 == 2 -> false
	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	// Float, 12.0 == 12.0 -> true
	vm.execute();
	ASSERT_EQ(1, vm.eval_stack_top().i());

	// Float, 12.0 == -99.0 -> false
	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	// Char, a == a -> true
	vm.execute();
	ASSERT_EQ(1, vm.eval_stack_top().i());

	// Char, a == b -> false
	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());
}

TEST_F(AreEqTest, StructEq)
{
	program_.emit(
	{
		new_struct, 0,
		s_local, 0,
		new_struct, 1,
		s_local, 1,
		l_local, 0,
		iconst, 10,
		ncall, 2,
		halt,
		iconst, 3,
		new_arr, (int)VMType::Int,
		l_local, 0,
		ncall, 2,
		halt,
		l_local, 0,
		l_local, 1,
		ncall, 2,
		halt,
		l_local, 0,
		l_local, 0,
		ncall, 2,
		halt,
		l_local, 1,
		l_local, 1,
		ncall, 2,
		halt,
	});

	auto vm = VM(program_);

	// Struct instance == int -> false
	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	// Array instance == Struct instance -> false
	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	// Different struct instances -> false
	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	// Same struct instance -> true
	vm.execute();
	ASSERT_EQ(1, vm.eval_stack_top().i());

	// Same struct instance -> true
	vm.execute();
	ASSERT_EQ(1, vm.eval_stack_top().i());
}
