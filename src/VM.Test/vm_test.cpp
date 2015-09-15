#pragma once

#include <gtest\gtest.h>

int vm_test_dummy() { return 0; }

TEST(test, test1)
{
	EXPECT_EQ(10, 10);
}
