#include "are_eq_test.h"

using namespace elsa;
using namespace elsa::vm;

int are_eq_test() { return 0; };

class AreEqTest : public testing::Test {
protected:
	virtual void SetUp()
	{
		auto si = std::make_unique<StructInfo>(L"my_struct");
		si->add_field(std::make_unique<FieldInfo>(L"field0", elsa::VMType::GCOPtr));
		si->add_field(std::make_unique<FieldInfo>(L"field1", elsa::VMType::GCOPtr));
		si->add_field(std::make_unique<FieldInfo>(L"field2", elsa::VMType::GCOPtr));
		program_.add_struct(std::move(si));

		auto si2 = std::make_unique<StructInfo>(L"my_struct2");
		si2->add_field(std::make_unique<FieldInfo>(L"field0", elsa::VMType::Int));
		program_.add_struct(std::move(si2));
	}

	virtual void TearDown() {}

	VMProgram program_;
};
