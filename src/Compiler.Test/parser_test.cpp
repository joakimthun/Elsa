#include "parser_test.h"

using namespace elsa;
using namespace elsa::compiler;

int parser_test() { return 0; }

TEST(ParserTest, DUMMY)
{
	auto lexer = new Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program1.elsa"));
	auto parser = ElsaParser(lexer);

	ASSERT_EQ(1, 1);
}