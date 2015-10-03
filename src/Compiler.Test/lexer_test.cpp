#include <gtest\gtest.h>

#include "lexing\lexer.h"

using namespace elsa;
using namespace elsa::compiler;

TEST(LexerTest, DUMMY)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\test_files\\source_file.el"));
	auto next_token = lexer.next_token();

	ASSERT_EQ(next_token.get_type(), TokenType::Var);
	ASSERT_EQ(next_token.get_value(), std::wstring(L"var"));
}