#include "array_test.h"

using namespace elsa;
using namespace elsa::vm;

int array_test() { return 0; };

class ArrayTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		program_.add_func(std::make_unique<FunctionInfo>(L"main", 0, 2, ep, FunctionType::Static));
		program_.add_float(std::make_unique<FloatInfo>(12.0f));
		program_.add_float(std::make_unique<FloatInfo>(99.0f));
		program_.add_float(std::make_unique<FloatInfo>(-99.0f));

		auto si = std::make_unique<StructInfo>(L"my_struct");
		si->add_field(std::make_unique<FieldInfo>(L"field0", elsa::VMType::Int));
		program_.add_struct(std::move(si));

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
		new_arr, (int)VMType::Int,
		halt
	});

	auto vm = VM(program_);
	vm.execute();

	ASSERT_EQ(elsa::VMType::GCOPtr, vm.eval_stack_top().get_type());
	EXPECT_EQ(GCObjectType::Array, vm.eval_stack_top().gco()->type);
}

TEST_F(ArrayTest, ADD)
{
	program_.emit(
	{
		iconst, 1,
		new_arr, (int)VMType::Int,
		s_local, 0,

		l_local, 0,
		halt,
		pop,
	
		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		halt,
		iconst, 3,
		l_ele,		
		halt,

		l_local, 0,
		iconst, 2,
		l_ele,
		halt,

		l_local, 0,
		iconst, 1,
		l_ele,
		halt,

		l_local, 0,
		iconst, 0,
		l_ele,
		halt,

	});
	
	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(0, vm.eval_stack_top().gco()->ai->next_index);

	vm.execute();
	ASSERT_EQ(4, vm.eval_stack_top().gco()->ai->next_index);
	ASSERT_EQ(4, vm.eval_stack_top().gco()->ai->num_elements);

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());
	
	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());
	
	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());
}

TEST_F(ArrayTest, INT_STORE_LOAD)
{
	program_.emit(
	{
		iconst, 3,
		new_arr, (int)VMType::Int,
		s_local, 0,

		// Store 10 at index 0
		l_local, 0,
		iconst, 10,
		a_ele,

		// Store -10 at index 1
		l_local, 0,
		iconst, -10,
		a_ele,

		// Store 12939 at index 2
		l_local, 0,
		iconst, 12939,
		a_ele,

		// Load element at index 0 (10)
		l_local, 0,
		iconst, 0,
		l_ele,
		halt,

		// Load element at index 1 (-10)
		l_local, 0,
		iconst, 1,
		l_ele,
		halt,

		// Load element at index 2 (12939)
		l_local, 0,
		iconst, 2,
		l_ele,
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
		new_arr, (int)VMType::Float,
		s_local, 0,

		// Store 12.0 at index 0
		l_local, 0,
		fconst, 0,
		a_ele, 

		// Store 99.0 at index 1
		l_local, 0,
		fconst, 1,
		a_ele,

		// Store -99.0 at index 2
		l_local, 0,
		fconst, 2,
		a_ele,

		// Load element at index 0 (12.0)
		l_local, 0,
		iconst, 0,
		l_ele,
		halt,

		// Load element at index 1 (99.0)
		l_local, 0,
		iconst, 1,
		l_ele,
		halt,

		// Load element at index 2 (-99.0)
		l_local, 0,
		iconst, 2,
		l_ele,
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
		new_arr, (int)VMType::GCOPtr,
		s_local, 0,

		// Store a struct pointer at index 0
		l_local, 0,
		new_struct, 0,
		a_ele,

		// Store another struct pointer at index 1
		l_local, 0,
		new_struct, 0,
		a_ele,

		// Store the value 4 in the struct pointed to by element 0
		l_local, 0,
		iconst, 0,
		l_ele,
		iconst, 4,
		s_field, 0,

		// Load the value(4) from the struct pointed to by element 0
		l_local, 0,
		iconst, 0,
		l_ele,
		l_field, 0,
		halt,
		pop,

		// Store the value -67 in the struct pointed to by element 1
		l_local, 0,
		iconst, 1,
		l_ele,
		iconst, -67,
		s_field, 0,

		// Load the value(-67) from the struct pointed to by element 1
		l_local, 0,
		iconst, 1,
		l_ele,
		l_field, 0,
		halt,
		pop,

		// Load the value(4) from the struct pointed to by element 0
		l_local, 0,
		iconst, 0,
		l_ele,
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
		new_arr, (int)VMType::GCOPtr,
		s_local, 0,

		l_local, 0,
		iconst, 2,
		new_arr, (int)VMType::Int,
		a_ele,

		l_local, 0,
		iconst, 2,
		new_arr, (int)VMType::Int,
		a_ele,

		l_local, 0,
		iconst, 0,
		l_ele,
		iconst, 10,
		a_ele,

		l_local, 0,
		iconst, 0,
		l_ele, 
		iconst, 20,
		a_ele,

		l_local, 0,
		iconst, 0,
		l_ele,
		iconst, 0,
		l_ele,
		halt,
		pop,

		l_local, 0,
		iconst, 0,
		l_ele,
		iconst, 1,
		l_ele,
		halt,
		pop,

		l_local, 0,
		iconst, 1,
		l_ele,
		iconst, 30,
		a_ele,

		l_local, 0,
		iconst, 1,
		l_ele,
		iconst, 40,
		a_ele,

		l_local, 0,
		iconst, 1,
		l_ele,
		iconst, 0,
		l_ele,
		halt,
		pop,

		l_local, 0,
		iconst, 1,
		l_ele,
		iconst, 1,
		l_ele,
		halt,
		pop,

		l_local, 0,
		iconst, 0,
		l_ele,
		iconst, 0,
		l_ele,
		halt,
		pop,

		l_local, 0,
		iconst, 0,
		l_ele,
		iconst, 1,
		l_ele,
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

TEST_F(ArrayTest, COPY)
{
	program_.emit(
	{
		iconst, 1,
		new_arr, (int)VMType::Int,
		s_local, 0,

		iconst, 1,
		new_arr, (int)VMType::Int,
		s_local, 1,

		// Add 3 elements to the source array
		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		halt,
		iconst, 0,
		l_ele,
		halt,

		l_local, 0,
		iconst, 1,
		l_ele,
		halt,

		l_local, 0,
		iconst, 2,
		l_ele,
		halt,

		// Copy the values from array 0 to to array 1
		// Push the taget
		l_local, 1,
		// Push the source
		l_local, 0,
		c_arr,

		l_local, 1,
		iconst, 0,
		l_ele,
		halt,

		l_local, 1,
		iconst, 1,
		l_ele,
		halt,

		l_local, 1,
		iconst, 2,
		l_ele,
		halt,

	});

	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(3, vm.eval_stack_top().gco()->ai->next_index);

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());
	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());
	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());
	
	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());
	
	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());
}

TEST_F(ArrayTest, REMOVE)
{
	program_.emit(
	{
		iconst, 1,
		new_arr, (int)VMType::Int,
		s_local, 0,

		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		halt,
		iconst, 0,
		l_ele,
		halt,
		pop,
		l_local, 0,
		iconst, 1,
		l_ele,
		halt,
		pop,
		l_local, 0,
		iconst, 2,
		l_ele,
		halt,
		pop,

		l_local, 0,
		r_ele, 1,
		l_local, 0,

		halt,
		iconst, 0,
		l_ele,
		halt,
		pop,
		l_local, 0,
		iconst, 1,
		l_ele,

	});

	auto vm = VM(program_);

	vm.execute();
	ASSERT_EQ(3, vm.eval_stack_top().gco()->ai->next_index);
	ASSERT_EQ(4, vm.eval_stack_top().gco()->ai->num_elements);

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());

	// Remove
	vm.execute();
	ASSERT_EQ(2, vm.eval_stack_top().gco()->ai->next_index);

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());

	vm.execute();
	ASSERT_EQ(-10, vm.eval_stack_top().i());

}

TEST_F(ArrayTest, POP)
{
	program_.emit(
	{
		iconst, 3,
		new_arr, (int)VMType::Int,
		s_local, 0,

		// Add element 1
		l_local, 0,
		iconst, 10,
		a_ele,

		// Add element 2
		l_local, 0,
		iconst, -10,
		a_ele,

		// Add element 3
		l_local, 0,
		iconst, 12939,
		a_ele,

		// Pop element 3
		l_local, 0,
		p_ele,
		halt,

		// Pop element 2
		l_local, 0,
		p_ele,
		halt,

		// Add element 2
		l_local, 0,
		iconst, 678,
		a_ele,

		// Pop element 2
		l_local, 0,
		p_ele,
		halt,

		// Pop element 1
		l_local, 0,
		p_ele,
		halt
	});

	auto vm = VM(program_);

	vm.execute();

	EXPECT_EQ(12939, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(-10, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(678, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(10, vm.eval_stack_top().i());
}

TEST_F(ArrayTest, LENGTH)
{
	program_.emit(
	{
		iconst, 5,
		new_arr, (int)VMType::Int,
		s_local, 0,

		// 1 element
		l_local, 0,
		iconst, 10,
		a_ele,

		l_local, 0,
		len_arr,
		halt,

		// 2 elements
		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		len_arr,
		halt,

		// 3 elements
		l_local, 0,
		iconst, 12939,
		a_ele,

		l_local, 0,
		len_arr,
		halt,

		// 4 elements
		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		len_arr,
		halt,

		// 5 elements
		l_local, 0,
		iconst, -10,
		a_ele,

		l_local, 0,
		len_arr,
		halt,

		// Pop element 5
		l_local, 0,
		p_ele,
		
		l_local, 0,
		len_arr,
		halt,

		// Pop element 4
		l_local, 0,
		p_ele,

		l_local, 0,
		len_arr,
		halt,

		// Pop element 3
		l_local, 0,
		p_ele,

		l_local, 0,
		len_arr,
		halt,

		// Pop element 2
		l_local, 0,
		p_ele,

		l_local, 0,
		len_arr,
		halt,

		// Pop element 1
		l_local, 0,
		p_ele,

		l_local, 0,
		len_arr,
		halt,

	});

	auto vm = VM(program_);

	vm.execute();

	EXPECT_EQ(1, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(2, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(3, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(4, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(5, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(4, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(3, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(2, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(1, vm.eval_stack_top().i());

	vm.execute();

	EXPECT_EQ(0, vm.eval_stack_top().i());

}