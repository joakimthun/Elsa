#include "struct_test.h"

using namespace elsa;
using namespace elsa::vm;

int struct_test() { return 0; };

class StructTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;
		vm_.constant_pool().add_func(new FunctionInfo("main", 0, 3, ep, FunctionType::Static));
		vm_.set_entry_point(ep);

		auto si = new StructInfo("my_struct");
		si->add_field(new FieldInfo("field0", elsa::OType::Int));
		si->add_field(new FieldInfo("field1", elsa::OType::Float));
		si->add_field(new FieldInfo("field2", elsa::OType::Int));
		si->add_field(new FieldInfo("field3", elsa::OType::Float));
		si->add_field(new FieldInfo("field4", elsa::OType::Int));
		vm_.constant_pool().add_struct(si);

		vm_.constant_pool().add_float(new FloatInfo(12.0f));
		vm_.constant_pool().add_float(new FloatInfo(99.0f));

		auto si2 = new StructInfo("my_struct2");
		si2->add_field(new FieldInfo("field0", elsa::OType::GCOPtr));
		si2->add_field(new FieldInfo("field1", elsa::OType::Int));
		si2->add_field(new FieldInfo("field2", elsa::OType::GCOPtr));

		vm_.constant_pool().add_struct(si2);

		auto si3 = new StructInfo("my_struct3");
		si3->add_field(new FieldInfo("field0", elsa::OType::GCOPtr));
		si3->add_field(new FieldInfo("field1", elsa::OType::Int));
		si3->add_field(new FieldInfo("field2", elsa::OType::Bool));
		si3->add_field(new FieldInfo("field3", elsa::OType::Char));
		si3->add_field(new FieldInfo("field4", elsa::OType::Float));

		vm_.constant_pool().add_struct(si3);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(StructTest, NEW)
{
	std::vector<int> p =
	{
		new_struct, 0
	};

	vm_.set_program(p);
	vm_.execute();

	auto obj = vm_.eval_stack_top();

	ASSERT_EQ(elsa::OType::GCOPtr, obj.get_type());

	auto si = obj.gco()->si;

	ASSERT_EQ("my_struct", si->get_name());
	ASSERT_EQ(20, si->get_size());
}

TEST_F(StructTest, FIELD_STORE_LOAD)
{
	std::vector<int> p =
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

TEST_F(StructTest, STRUCT_FIELD_STORE_LOAD)
{
	std::vector<int> p =
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
	};

	vm_.set_program(p);

	vm_.execute();
	ASSERT_EQ("my_struct", vm_.eval_stack_top().gco()->si->get_name());

	vm_.execute();
	ASSERT_EQ("my_struct2", vm_.eval_stack_top().gco()->si->get_name());

	vm_.execute();
	ASSERT_EQ("my_struct", vm_.eval_stack_top().gco()->si->get_name());

	vm_.execute();
	ASSERT_EQ("my_struct2", vm_.eval_stack_top().gco()->si->get_name());

	vm_.execute();
	ASSERT_EQ("my_struct", vm_.eval_stack_top().gco()->si->get_name());

	vm_.execute();
	ASSERT_EQ(77, vm_.eval_stack_top().i());
}

TEST_F(StructTest, STRUCT_ON_STRUCT_FIELD_STORE_LOAD)
{
	std::vector<int> p =
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
	};

	vm_.set_program(p);

	vm_.execute();
	ASSERT_EQ("my_struct", vm_.eval_stack_top().gco()->si->get_name());

	vm_.execute();
	ASSERT_EQ("my_struct2", vm_.eval_stack_top().gco()->si->get_name());

	vm_.execute();
	ASSERT_EQ(12378, vm_.eval_stack_top().i());

	vm_.execute();
	ASSERT_EQ("my_struct2", vm_.eval_stack_top().gco()->si->get_name());

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

TEST_F(StructTest, FIELD_DEFAULT_VALUES)
{
	std::vector<int> p =
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
	};

	vm_.set_program(p);

	vm_.execute();
	ASSERT_EQ("my_struct3", vm_.eval_stack_top().gco()->si->get_name());

	vm_.execute();
	ASSERT_EQ(nullptr, vm_.eval_stack_top().gco());

	vm_.execute();
	ASSERT_EQ(0, vm_.eval_stack_top().i());

	vm_.execute();
	ASSERT_EQ(false, vm_.eval_stack_top().b());

	vm_.execute();
	ASSERT_EQ('\0', vm_.eval_stack_top().c());

	vm_.execute();
	ASSERT_FLOAT_EQ(0.0f, vm_.eval_stack_top().f());
}
