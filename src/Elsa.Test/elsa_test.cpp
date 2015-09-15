#include <gtest\gtest.h>

#include "vm_test.h"

int x = vm_test_dummy();

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

