#include <gtest\gtest.h>

#include "vm.h"

using namespace elsa::vm;

class GCTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		int ep = 0;

		vm_.add_constant_entry(new FunctionInfo("main", 0, 1, ep, FunctionType::Static));

		auto si = new StructInfo("my_struct");
		si->add_field(new FieldInfo("field0", OType::GCOPtr));
		//si->add_field(new FieldInfo("field1", OType::GCOPtr));
		//si->add_field(new FieldInfo("field2", OType::GCOPtr));
		vm_.add_constant_entry(si);

		auto si2 = new StructInfo("my_struct2");
		si2->add_field(new FieldInfo("field0", OType::Int));
		vm_.add_constant_entry(si2);

		vm_.set_entry_point(ep);
	}

	virtual void TearDown() {}

	VM vm_;
};

TEST_F(GCTest, MARK)
{
	std::vector<int> p =
	{
		new_struct, 1,
		s_local, 0,

		//l_local, 0,
		//new_struct, 2,
		//s_field, 0,
	};

	vm_.set_program(p);

	vm_.execute();
	auto result = vm_.gc_collect();

	ASSERT_EQ(1, result.num_marked);
}
