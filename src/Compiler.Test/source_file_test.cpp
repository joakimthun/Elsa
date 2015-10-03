#include <gtest\gtest.h>
#include <string>

#include "lexing\source_file.h"

using namespace elsa;
using namespace elsa::compiler;

TEST(SOURCE_FILE, READ_ENTIRE_FILE)
{
	SourceFile sf("..\\Compiler.Test\\test_files\\source_file.el");
	std::wstring expected = L"var x = 10;";
	std::wstring result;

	wchar_t c = sf.next_char();
	while (c != '\0')
	{
		result += c;
	}

	ASSERT_EQ(expected, result);
}