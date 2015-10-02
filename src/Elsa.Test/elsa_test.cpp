#include <gtest\gtest.h>

#include "vm_test.cpp"
#include "compiler_test.cpp"

// When the Visual C++ linker sees nothing in the referenced library it throws the library out so we need to use something from it so gtest can find all tests.
int x = vm_test_dummy();
int x2 = compiler_test_dummy();

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

