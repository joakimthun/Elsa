#include "array_test.h"

using namespace elsa;
using namespace elsa::vm;

int array_test() { return 0; };

class ArrayTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		program_.add_func(new FunctionInfo(L"main", 0, 2, ep, FunctionType::Static));
		program_.add_float(new FloatInfo(12.0f));
		program_.add_float(new FloatInfo(99.0f));
		program_.add_float(new FloatInfo(-99.0f));

		auto si = new StructInfo("my_struct");
		si->add_field(new FieldInfo("field0", elsa::OType::Int));
		program_.add_struct(si);

		program_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(ArrayTest, NEW)
{
	program_.emit(
	{
		iconst, 3,
		new_arr, Int,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	ASSERT_EQ(elsa::OType::GCOPtr, vm.eval_stack_top().get_type());
	EXPECT_EQ(GCObjectType::Array, vm.eval_stack_top().gco()->type);
}

TEST_F(ArrayTest, RESIZE)
{
	program_.emit(
	{
		iconst, 3,
		new_arr, Int,
		s_local, 0,

		l_local, 0,
		iconst, 100,
		s_ele, 0,

		l_local, 0,
		iconst, 200,
		s_ele, 1,

		l_local, 0,
		iconst, 300,
		s_ele, 2,

		l_local, 0,
		l_ele, 0,
		halt,
		pop,

		l_local, 0,
		l_ele, 1,
		halt,
		pop,

		l_local, 0,
		l_ele, 2,
		halt,
		pop,

		// Resize from 3 to 7 ints
		l_local, 0,
		iconst, 7,
		res_arr,

		l_local, 0,
		l_ele, 0,
		halt,
		pop,

		l_local, 0,
		l_ele, 1,
		halt,
		pop,

		l_local, 0,
		l_ele, 2,
		halt,
		pop,

		l_local, 0,
		l_ele, 3,
		halt,
		pop,

		l_local, 0,
		l_ele, 4,
		halt,
		pop,

		l_local, 0,
		l_ele, 5,
		halt,
		pop,

		l_local, 0,
		l_ele, 6,
		halt,
	});

	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(100, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(200, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(300, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(100, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(200, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(300, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().i());
}

TEST_F(ArrayTest, INT_STORE_LOAD)
{
	program_.emit(
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
	});

	auto vm = VM(program_);

	vm.execute();

	EXPECT_EQ(10, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(-10, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(12939, vm.eval_stack_top().i());
}

TEST_F(ArrayTest, FLOAT_STORE_LOAD)
{
	program_.emit(
	{
		iconst, 3,
		new_arr, Float,
		s_local, 0,

		// Store 12.0 at index 0
		l_local, 0,
		fconst, 0,
		s_ele, 0,

		// Store 99.0 at index 1
		l_local, 0,
		fconst, 1,
		s_ele, 1,

		// Store -99.0 at index 2
		l_local, 0,
		fconst, 2,
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
	});

	auto vm = VM(program_);

	vm.execute();

	EXPECT_FLOAT_EQ(12.0f, vm.eval_stack_top().f());

	vm.execute();

	EXPECT_FLOAT_EQ(99.0f, vm.eval_stack_top().f());

	vm.execute();

	EXPECT_FLOAT_EQ(-99.0f, vm.eval_stack_top().f());
}

TEST_F(ArrayTest, STRUCT_PTR_STORE_LOAD)
{
	program_.emit(
	{
		iconst, 2,
		new_arr, GCOPtr,
		s_local, 0,

		// Store a struct pointer at index 0
		l_local, 0,
		new_struct, 0,
		s_ele, 0,

		// Store another struct pointer at index 1
		l_local, 0,
		new_struct, 0,
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

	});

	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(4, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(-67, vm.eval_stack_top().i());

	// Assert field 0 of struct ptr at index 0 is unchanged
	vm.execute();
	ASSERT_EQ(4, vm.eval_stack_top().i());
}

TEST_F(ArrayTest, ARRAY_OF_ARRAYS)
{
	program_.emit(
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
	});

	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(10, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(20, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(30, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(40, vm.eval_stack_top().i());

	// Assert the first array is unchanged after storing values in the second array
	vm.execute();
	ASSERT_EQ(10, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(20, vm.eval_stack_top().i());
}

TEST_F(ArrayTest, DEFAULT_VALUES)
{
	program_.emit(
	{
		iconst, 2,
		new_arr, Float,
		s_local, 0,

		halt,
		iconst, 2,
		new_arr, Char,
		s_local, 1,

		l_local, 0,
		l_ele, 0,
		halt,
		pop,

		l_local, 0,
		l_ele, 1,
		halt,
		pop,

		l_local, 1,
		l_ele, 0,
		halt,
		pop,

		l_local, 1,
		l_ele, 1,
		halt,
		pop,
	});

	auto vm = VM(program_);
	vm.execute();

	vm.execute();
	ASSERT_FLOAT_EQ(0.0f, vm.eval_stack_top().f());

	vm.execute();
	ASSERT_FLOAT_EQ(0.0f, vm.eval_stack_top().f());

	vm.execute();
	ASSERT_EQ('\0', vm.eval_stack_top().c());

	vm.execute();
	ASSERT_EQ('\0', vm.eval_stack_top().c());
}