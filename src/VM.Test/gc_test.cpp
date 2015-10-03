#include "gc_test.h"

using namespace elsa;
using namespace elsa::vm;

int gc_test() { return 0; };

class GCTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		auto si = new StructInfo("my_struct");
		si->add_field(new FieldInfo("field0", elsa::OType::GCOPtr));
		si->add_field(new FieldInfo("field1", elsa::OType::GCOPtr));
		si->add_field(new FieldInfo("field2", elsa::OType::GCOPtr));
		vm_.constant_pool().add_struct(si);

		auto si2 = new StructInfo("my_struct2");
		si2->add_field(new FieldInfo("field0", elsa::OType::Int));
		vm_.constant_pool().add_struct(si2);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(GCTest, COLLECT_NO_SWEEP)
{
	vm_.constant_pool().add_func(new FunctionInfo("main", 0, 1, 0, FunctionType::Static));
	vm_.set_entry_point(0);

	std::vector<int> p =
	{
		new_struct, 0,
		s_local, 0,

		l_local, 0,
		new_struct, 1,
		s_field, 0,

		l_local, 0,
		new_struct, 0,
		s_field, 1,

		l_local, 0,
		new_struct, 1,
		s_field, 2,

		l_local, 0,
		l_field, 1,
		new_struct, 0,
		s_field, 0
	};

	vm_.set_program(p);

	vm_.execute();
	auto result = vm_.gc_collect();
	ASSERT_EQ(5, result.num_marked);
	ASSERT_EQ(0, result.num_swept);
}

TEST_F(GCTest, COLLECT_POPPED_OBJECTS)
{
	vm_.constant_pool().add_func(new FunctionInfo("main", 0, 1, 0, FunctionType::Static));
	vm_.set_entry_point(0);

	std::vector<int> p =
	{
		new_struct, 0,
		pop,

		new_struct, 0,
		pop,

		new_struct, 1,
		pop,

		iconst, 7,
		new_arr, Int,
		pop,

		new_struct, 0,
		pop,
	};

	vm_.set_program(p);

	vm_.execute();
	auto result = vm_.gc_collect();
	ASSERT_EQ(0, result.num_marked);
	ASSERT_EQ(5, result.num_swept);
}

TEST_F(GCTest, SWEEP_OBJECTS_FROM_POPPED_STACK_FRAME)
{
	vm_.constant_pool().add_func(new FunctionInfo("main", 0, 1, 11, FunctionType::Static));
	vm_.constant_pool().add_func(new FunctionInfo("my_func", 0, 1, 0, FunctionType::Static));
	vm_.set_entry_point(11);

	std::vector<int> p =
	{
		new_struct, 0,
		s_local, 0,
		l_local, 0,
		new_struct, 1,
		s_field, 0,
		ret,

		call, 0,
		new_struct, 0,
		s_local, 0,
	};

	vm_.set_program(p);

	vm_.execute();
	auto result = vm_.gc_collect();

	// Since my_func has been popped of the call stack we should only have 1 marked object for gc(the one created in main)
	ASSERT_EQ(1, result.num_marked);
	ASSERT_EQ(2, result.num_swept);
}

TEST_F(GCTest, MARK_SWEEP_ARRAYS)
{
	vm_.constant_pool().add_func(new FunctionInfo("main", 0, 4, 0, FunctionType::Static));
	vm_.set_entry_point(0);

	std::vector<int> p =
	{
		iconst, 7,
		new_arr, Int,
		s_local, 0,
		
		iconst, 2,
		new_arr, Int,
		s_local, 1,
		
		iconst, 5,
		new_arr, GCOPtr,
		s_local, 2,
		
		l_local, 2,
		new_struct, 0,
		s_ele, 0,

		iconst, 2,
		new_arr, Int,
		pop,

		iconst, 2,
		new_arr, Int,
		pop,

		iconst, 5,
		new_arr, GCOPtr,
		s_local, 3,

		l_local, 3,
		iconst, 5,
		new_arr, GCOPtr,
		s_ele, 2,
	};

	vm_.set_program(p);

	vm_.execute();
	auto result = vm_.gc_collect();
	ASSERT_EQ(6, result.num_marked);
	ASSERT_EQ(2, result.num_swept);
}