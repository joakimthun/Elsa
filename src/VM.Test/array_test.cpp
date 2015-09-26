#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

class ArrayTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		vm_.add_constant_entry(new FunctionInfo("main", 0, 1, ep, FunctionType::Static));
		vm_.add_constant_entry(new FloatEntry(12.0f));
		vm_.add_constant_entry(new FloatEntry(99.0f));
		vm_.add_constant_entry(new FloatEntry(-99.0f));

		auto si = new StructInfo("my_struct");
		si->add_field(new FieldInfo("field0", OType::Int));
		vm_.add_constant_entry(si);

		vm_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(ArrayTest, NEW)
{
	std::vector<int> p =
	{
		iconst, 3,
		new_arr, Int,
		halt
	};

	vm_.set_program(p);

	vm_.execute();

	ASSERT_EQ(OType::GCOPtr, vm_.eval_stack_top().get_type());
	EXPECT_EQ(GCObjectType::Array, vm_.eval_stack_top().gco()->type);
}

TEST_F(ArrayTest, INT_STORE_LOAD)
{
	std::vector<int> p =
	{
		iconst, 3,
		new_arr, Int, 
		s_local, 0,

		// Store 10 at index 0
		l_local, 0,
		iconst, 10,
		s_ele, 0,

		// Store -10 at index 1
		l_local, 0,
		iconst, -10,
		s_ele, 1,

		// Store 12939 at index 2
		l_local, 0,
		iconst, 12939,
		s_ele, 2,

		// Load element at index 0 (10)
		l_local, 0,
		l_ele, 0,
		halt,

		// Load element at index 1 (-10)
		l_local, 0,
		l_ele, 1,
		halt,

		// Load element at index 2 (12939)
		l_local, 0,
		l_ele, 2,
		halt
	};

	vm_.set_program(p);

	vm_.execute();

	EXPECT_EQ(10, vm_.eval_stack_top().i());

	vm_.execute();

	EXPECT_EQ(-10, vm_.eval_stack_top().i());

	vm_.execute();

	EXPECT_EQ(12939, vm_.eval_stack_top().i());
}

TEST_F(ArrayTest, FLOAT_STORE_LOAD)
{
	std::vector<int> p =
	{
		iconst, 3,
		new_arr, Float,
		s_local, 0,

		// Store 12.0 at index 0
		l_local, 0,
		fconst, 1,
		s_ele, 0,

		// Store 99.0 at index 1
		l_local, 0,
		fconst, 2,
		s_ele, 1,

		// Store -99.0 at index 2
		l_local, 0,
		fconst, 3,
		s_ele, 2,

		// Load element at index 0 (12.0)
		l_local, 0,
		l_ele, 0,
		halt,

		// Load element at index 1 (99.0)
		l_local, 0,
		l_ele, 1,
		halt,

		// Load element at index 2 (-99.0)
		l_local, 0,
		l_ele, 2,
		halt
	};

	vm_.set_program(p);

	vm_.execute();

	EXPECT_FLOAT_EQ(12.0f, vm_.eval_stack_top().f());

	vm_.execute();

	EXPECT_FLOAT_EQ(99.0f, vm_.eval_stack_top().f());

	vm_.execute();

	EXPECT_FLOAT_EQ(-99.0f, vm_.eval_stack_top().f());
}

TEST_F(ArrayTest, STRUCT_PTR_STORE_LOAD)
{
	std::vector<int> p =
	{
		iconst, 2,
		new_arr, GCOPtr,
		s_local, 0,

		// Store a struct pointer at index 0
		l_local, 0,
		new_struct, 4,
		s_ele, 0,

		// Store another struct pointer at index 1
		l_local, 0,
		new_struct, 4,
		s_ele, 1,

		// Store the value 4 in the struct pointed to by element 0
		l_local, 0,
		l_ele, 0,
		iconst, 4,
		s_field, 0,

		// Load the value(4) from the struct pointed to by element 0
		l_local, 0,
		l_ele, 0,
		l_field, 0,
		halt,
		pop,

		// Store the value -67 in the struct pointed to by element 1
		l_local, 0,
		l_ele, 1,
		iconst, -67,
		s_field, 0,

		// Load the value(-67) from the struct pointed to by element 1
		l_local, 0,
		l_ele, 1,
		l_field, 0,
		halt,
		pop,

		// Load the value(4) from the struct pointed to by element 0
		l_local, 0,
		l_ele, 0,
		l_field, 0,
		halt,
		pop,

	};

	vm_.set_program(p);

	vm_.execute();
	ASSERT_EQ(4, vm_.eval_stack_top().i());

	vm_.execute();
	ASSERT_EQ(-67, vm_.eval_stack_top().i());

	// Assert field 0 of struct ptr at index 0 is unchanged
	vm_.execute();
	ASSERT_EQ(4, vm_.eval_stack_top().i());
}

TEST_F(ArrayTest, ARRAY_OF_ARRAYS)
{
	std::vector<int> p =
	{
		iconst, 2,
		new_arr, GCOPtr,
		s_local, 0,

		l_local, 0,
		iconst, 2,
		new_arr, Int,
		s_ele, 0,

		l_local, 0,
		iconst, 2,
		new_arr, Int,
		s_ele, 1,

		l_local, 0,
		l_ele, 0,
		iconst, 10,
		s_ele, 0,

		l_local, 0,
		l_ele, 0,
		iconst, 20,
		s_ele, 1,

		l_local, 0,
		l_ele, 0,
		l_ele, 0,
		halt,
		pop,

		l_local, 0,
		l_ele, 0,
		l_ele, 1,
		halt,
		pop,

		l_local, 0,
		l_ele, 1,
		iconst, 30,
		s_ele, 0,

		l_local, 0,
		l_ele, 1,
		iconst, 40,
		s_ele, 1,

		l_local, 0,
		l_ele, 1,
		l_ele, 0,
		halt,
		pop,

		l_local, 0,
		l_ele, 1,
		l_ele, 1,
		halt,
		pop,

		l_local, 0,
		l_ele, 0,
		l_ele, 0,
		halt,
		pop,

		l_local, 0,
		l_ele, 0,
		l_ele, 1,
	};

	vm_.set_program(p);

	vm_.execute();
	ASSERT_EQ(10, vm_.eval_stack_top().i());

	vm_.execute();
	ASSERT_EQ(20, vm_.eval_stack_top().i());

	vm_.execute();
	ASSERT_EQ(30, vm_.eval_stack_top().i());

	vm_.execute();
	ASSERT_EQ(40, vm_.eval_stack_top().i());

	// Assert the first array is unchanged after storing values in the second array
	vm_.execute();
	ASSERT_EQ(10, vm_.eval_stack_top().i());

	vm_.execute();
	ASSERT_EQ(20, vm_.eval_stack_top().i());
}
