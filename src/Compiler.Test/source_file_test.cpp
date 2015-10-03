#include "source_file_test.h"

using namespace elsa;
using namespace elsa::compiler;

int source_file_test() { return 0; }

TEST(SOURCE_FILE, READ_ENTIRE_FILE)
{
	SourceFile sf("..\\Compiler.Test\\test_files\\sf.txt");
	std::wstring expected = L"var x = 10;";
	std::wstring result;

	while (sf.good())
	{
		result += sf.next_char();
	}

	ASSERT_EQ(L'v', result[0]);
	ASSERT_EQ(L'a', result[1]);
	ASSERT_EQ(L'r', result[2]);
	ASSERT_EQ(L' ', result[3]);
	ASSERT_EQ(L'x', result[4]);
	ASSERT_EQ(L' ', result[5]);
	ASSERT_EQ(L'=', result[6]);
	ASSERT_EQ(L' ', result[7]);
	ASSERT_EQ(L'1', result[8]);
	ASSERT_EQ(L'0', result[9]);
	ASSERT_EQ(L';', result[10]);
}