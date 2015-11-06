#include "gc_test.h"

using namespace elsa;
using namespace elsa::vm;

int gc_test() { return 0; };

class GCTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		auto si = new StructInfo(L"my_struct");
		si->add_field(new FieldInfo(L"field0", elsa::OType::GCOPtr));
		si->add_field(new FieldInfo(L"field1", elsa::OType::GCOPtr));
		si->add_field(new FieldInfo(L"field2", elsa::OType::GCOPtr));
		program_.add_struct(si);

		auto si2 = new StructInfo(L"my_struct2");
		si2->add_field(new FieldInfo(L"field0", elsa::OType::Int));
		program_.add_struct(si2);
	}

	virtual void TearDown() {}

	VMProgram program_;
};

TEST_F(GCTest, COLLECT_NO_SWEEP)
{
	program_.add_func(new FunctionInfo(L"main", 0, 1, 0, FunctionType::Static));
	program_.set_entry_point(0);

	program_.emit(
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
	});

	auto vm = VM(program_);

	vm.execute();
	auto result = vm.gc_collect();
	ASSERT_EQ(5, result.num_marked);
	ASSERT_EQ(0, result.num_swept);
}

TEST_F(GCTest, COLLECT_POPPED_OBJECTS)
{
	program_.add_func(new FunctionInfo(L"main", 0, 1, 0, FunctionType::Static));
	program_.set_entry_point(0);

	program_.emit(
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
	});

	auto vm = VM(program_);

	vm.execute();
	auto result = vm.gc_collect();
	ASSERT_EQ(0, result.num_marked);
	ASSERT_EQ(5, result.num_swept);
}

TEST_F(GCTest, SWEEP_OBJECTS_FROM_POPPED_STACK_FRAME)
{
	program_.add_func(new FunctionInfo(L"main", 0, 1, 11, FunctionType::Static));
	program_.add_func(new FunctionInfo(L"my_func", 0, 1, 0, FunctionType::Static));
	program_.set_entry_point(11);

	program_.emit(
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
	});

	auto vm = VM(program_);

	vm.execute();
	auto result = vm.gc_collect();

	// Since my_func has been popped of the call stack we should only have 1 marked object for gc(the one created in main)
	ASSERT_EQ(1, result.num_marked);
	ASSERT_EQ(2, result.num_swept);
}

TEST_F(GCTest, MARK_SWEEP_ARRAYS)
{
	program_.add_func(new FunctionInfo(L"main", 0, 4, 0, FunctionType::Static));
	program_.set_entry_point(0);

	program_.emit(
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
	});

	auto vm = VM(program_);

	vm.execute();
	auto result = vm.gc_collect();
	ASSERT_EQ(6, result.num_marked);
	ASSERT_EQ(2, result.num_swept);
}