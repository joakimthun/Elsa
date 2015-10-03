#include <gtest\gtest.h>

#include "vm_test.h"
#include "compiler_test.h"

// When the Visual C++ linker sees nothing in the referenced library it throws the library out so we need to use something from it so gtest can find all tests.
int v_test = vm_test();
int c_test = compiler_test();

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

