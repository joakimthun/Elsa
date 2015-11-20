#include "struct_test.h"

using namespace elsa;
using namespace elsa::vm;

int struct_test() { return 0; };

class StructTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;
		program_.add_func(std::make_unique<FunctionInfo>(L"main", 0, 3, ep, FunctionType::Static));
		program_.set_entry_point(ep);

		auto si = std::make_unique<StructInfo>(L"my_struct");
		si->add_field(std::make_unique<FieldInfo>(L"field0", elsa::VMType::Int));
		si->add_field(std::make_unique<FieldInfo>(L"field1", elsa::VMType::Float));
		si->add_field(std::make_unique<FieldInfo>(L"field2", elsa::VMType::Int));
		si->add_field(std::make_unique<FieldInfo>(L"field3", elsa::VMType::Float));
		si->add_field(std::make_unique<FieldInfo>(L"field4", elsa::VMType::Int));
		program_.add_struct(std::move(si));

		program_.add_float(std::make_unique<FloatInfo>(12.0f));
		program_.add_float(std::make_unique<FloatInfo>(99.0f));

		auto si2 = std::make_unique<StructInfo>(L"my_struct2");
		si2->add_field(std::make_unique<FieldInfo>(L"field0", elsa::VMType::GCOPtr));
		si2->add_field(std::make_unique<FieldInfo>(L"field1", elsa::VMType::Int));
		si2->add_field(std::make_unique<FieldInfo>(L"field2", elsa::VMType::GCOPtr));

		program_.add_struct(std::move(si2));

		auto si3 = std::make_unique<StructInfo>(L"my_struct3");
		si3->add_field(std::make_unique<FieldInfo>(L"field0", elsa::VMType::GCOPtr));
		si3->add_field(std::make_unique<FieldInfo>(L"field1", elsa::VMType::Int));
		si3->add_field(std::make_unique<FieldInfo>(L"field2", elsa::VMType::Int));
		si3->add_field(std::make_unique<FieldInfo>(L"field3", elsa::VMType::Char));
		si3->add_field(std::make_unique<FieldInfo>(L"field4", elsa::VMType::Float));

		program_.add_struct(std::move(si3));
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(StructTest, NEW)
{
	program_.emit(
	{
		new_struct, 0
	});

	auto vm = VM(program_);
	vm.execute();

	auto obj = vm.eval_stack_top();

	ASSERT_EQ(elsa::VMType::GCOPtr, obj.get_type());

	auto si = obj.gco()->si;

	ASSERT_EQ(L"my_struct", si->get_name());
	ASSERT_EQ(20, si->get_size());
}

TEST_F(StructTest, FIELD_STORE_LOAD)
{
	program_.emit(
	{
		new_struct, 0,
		s_local, 0,

		// Store 77 in field 0 (int)
		l_local, 0,
		iconst, 77,
		s_field, 0,

		// Store 12.0 in field 1 (float)
		l_local, 0,
		fconst, 0,
		s_field, 1,

		// Store 100 in field 2 (int)
		l_local, 0,
		iconst, 100,
		s_field, 2,

		// Store 99.0 in field 3 (float)
		l_local, 0,
		fconst, 1,
		s_field, 3,

		// Store -1829 in field 4 (int)
		l_local, 0,
		iconst, -1829,
		s_field, 4,

		// Load field 0
		l_local, 0,
		l_field, 0,
		halt,

		// Load field 1
		l_local, 0,
		l_field, 1,
		halt,

		// Load field 2
		l_local, 0,
		l_field, 2,
		halt,

		// Load field 3
		l_local, 0,
		l_field, 3,
		halt,

		// Load field 4
		l_local, 0,
		l_field, 4,
		halt,
	});

	auto vm = VM(program_);
	vm.execute();
	
	ASSERT_EQ(77, vm.eval_stack_top().i());

	vm.execute();

	ASSERT_FLOAT_EQ(12.0f, vm.eval_stack_top().f());

	vm.execute();

	ASSERT_EQ(100, vm.eval_stack_top().i());

	vm.execute();

	ASSERT_FLOAT_EQ(99.0f, vm.eval_stack_top().f());

	vm.execute();

	ASSERT_EQ(-1829, vm.eval_stack_top().i());
}

TEST_F(StructTest, STRUCT_FIELD_STORE_LOAD)
{
	program_.emit(
	{
		new_struct, 0,
		s_local, 0,

		// Store 77 in field 0 (int)
		l_local, 0,
		halt,
		iconst, 77,
		s_field, 0,

		new_struct, 1,
		s_local, 1,

		// Store a pointer to the fist struct in field 0 of the second struct
		l_local, 1,
		halt,
		l_local, 0,
		halt,
		s_field, 0,

		l_local, 1,
		halt,
		l_field, 0,
		halt,
		l_field, 0,
	});

	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(L"my_struct", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(L"my_struct2", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(L"my_struct", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(L"my_struct2", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(L"my_struct", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(77, vm.eval_stack_top().i());
}

TEST_F(StructTest, STRUCT_ON_STRUCT_FIELD_STORE_LOAD)
{
	program_.emit(
	{
		new_struct, 0,
		s_local, 0,

		l_local, 0,
		iconst, 77,
		s_field, 0,

		l_local, 0,
		fconst, 0,
		s_field, 1,

		l_local, 0,
		iconst, 100,
		s_field, 2,

		l_local, 0,
		fconst, 1,
		s_field, 3,

		l_local, 0,
		iconst, -1829,
		s_field, 4,

		new_struct, 1,
		s_local, 1,

		l_local, 1,
		l_local, 0,
		halt,
		s_field, 0,

		l_local, 1,
		iconst, 12378,
		s_field, 1,

		new_struct, 1,
		halt,
		s_local, 2,

		l_local, 2,
		l_local, 0,
		s_field, 0,

		l_local, 1,
		l_local, 2,
		s_field, 2,

		l_local, 1,
		l_field, 1,
		halt,
		pop,

		l_local, 1,
		l_field, 2,
		halt, 
		pop,

		// Load 77(field 0) from a pointer to struct 0
		l_local, 1,
		l_field, 2,
		l_field, 0,
		l_field, 0,
		halt,
		pop,

		// Load 12.0f(field 1) from a pointer to struct 0
		l_local, 1,
		l_field, 2,
		l_field, 0,
		l_field, 1,
		halt,
		pop,

		// Load 100(field 2) from a pointer to struct 0
		l_local, 1,
		l_field, 2,
		l_field, 0,
		l_field, 2,
		halt,
		pop,

		// Load 99.0f(field 3) from a pointer to struct 0
		l_local, 1,
		l_field, 2,
		l_field, 0,
		l_field, 3,
		halt,
		pop,

		// Load -1829(field 4) from a pointer to struct 0
		l_local, 1,
		l_field, 2,
		l_field, 0,
		l_field, 4,
		halt,
	});

	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(L"my_struct", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(L"my_struct2", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(12378, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(L"my_struct2", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(77, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_FLOAT_EQ(12.0f, vm.eval_stack_top().f());

	vm.execute();
	ASSERT_EQ(100, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_FLOAT_EQ(99.0f, vm.eval_stack_top().f());

	vm.execute();
	ASSERT_EQ(-1829, vm.eval_stack_top().i());
}

TEST_F(StructTest, FIELD_DEFAULT_VALUES)
{
	program_.emit(
	{
		new_struct, 2,
		s_local, 0,
		l_local, 0,
		halt,

		l_field, 0,
		halt,
		pop,

		l_local, 0,
		l_field, 1,
		halt,
		pop,

		l_local, 0,
		l_field, 2,
		halt,
		pop,

		l_local, 0,
		l_field, 3,
		halt,
		pop,

		l_local, 0,
		l_field, 4,
		halt
	});

	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(L"my_struct3", vm.eval_stack_top().gco()->si->get_name());

	vm.execute();
	ASSERT_EQ(nullptr, vm.eval_stack_top().gco());

	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ('\0', vm.eval_stack_top().c());

	vm.execute();
	ASSERT_FLOAT_EQ(0.0f, vm.eval_stack_top().f());
}
