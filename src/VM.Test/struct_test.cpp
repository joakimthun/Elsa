#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

class StructTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;
		vm_.add_constant_entry(new FunctionInfo("main", 0, 1, ep, FunctionType::Static));
		vm_.set_entry_point(ep);

		auto si = new StructInfo("my_struct");
		si->add_field(new FieldInfo("field0", OType::Int));
		si->add_field(new FieldInfo("field1", OType::Float));
		si->add_field(new FieldInfo("field2", OType::Int));
		si->add_field(new FieldInfo("field3", OType::Float));
		si->add_field(new FieldInfo("field4", OType::Int));

		vm_.add_constant_entry(si);

		vm_.add_constant_entry(new FloatEntry(12.0f));
		vm_.add_constant_entry(new FloatEntry(99.0f));
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(StructTest, NEW_STRUCT)
{
	std::vector<int> p =
	{
		new_struct, 1
	};

	vm_.set_program(p);
	vm_.execute();

	auto obj = vm_.eval_stack_top();

	ASSERT_EQ(OType::GCOPtr, obj.get_type());

	auto si = obj.gco()->si;

	ASSERT_EQ("my_struct", si->get_name());
	ASSERT_EQ(20, si->get_size());
}

TEST_F(StructTest, FIELD_STORE_LOAD)
{
	std::vector<int> p =
	{
		new_struct, 1,
		s_local, 0,

		// Store 77 in field 0 (int)
		l_local, 0,
		iconst, 77,
		s_field, 0,

		// Store 12.0 in field 1 (float)
		l_local, 0,
		fconst, 2,
		s_field, 1,

		// Store 100 in field 2 (int)
		l_local, 0,
		iconst, 100,
		s_field, 2,

		// Store 99.0 in field 3 (float)
		l_local, 0,
		fconst, 3,
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
	};

	vm_.set_program(p);
	vm_.execute();
	
	ASSERT_EQ(77, vm_.eval_stack_top().i());

	vm_.execute();

	ASSERT_FLOAT_EQ(12.0f, vm_.eval_stack_top().f());

	vm_.execute();

	ASSERT_EQ(100, vm_.eval_stack_top().i());

	vm_.execute();

	ASSERT_FLOAT_EQ(99.0f, vm_.eval_stack_top().f());

	vm_.execute();

	ASSERT_EQ(-1829, vm_.eval_stack_top().i());
}