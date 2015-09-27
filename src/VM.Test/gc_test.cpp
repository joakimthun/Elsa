#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

class GCTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		auto si = new StructInfo("my_struct");
		si->add_field(new FieldInfo("field0", OType::GCOPtr));
		si->add_field(new FieldInfo("field1", OType::GCOPtr));
		si->add_field(new FieldInfo("field2", OType::GCOPtr));
		vm_.add_constant_entry(si);

		auto si2 = new StructInfo("my_struct2");
		si2->add_field(new FieldInfo("field0", OType::Int));
		vm_.add_constant_entry(si2);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(GCTest, BASIC_MARK_STRUCTS)
{
	vm_.add_constant_entry(new FunctionInfo("main", 0, 1, 0, FunctionType::Static));
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
}

TEST_F(GCTest, BASIC_CALL_MARK_STRUCTS)
{
	vm_.add_constant_entry(new FunctionInfo("main", 0, 1, 11, FunctionType::Static));
	vm_.add_constant_entry(new FunctionInfo("my_func", 0, 1, 0, FunctionType::Static));
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
}
