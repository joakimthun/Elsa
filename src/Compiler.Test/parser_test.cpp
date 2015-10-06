#include "parser_test.h"

using namespace elsa;
using namespace elsa::compiler;

int parser_test() { return 0; }

TEST(ParserTest, PREFIX_OPERATOR_IDENTIFIER)
{
	auto lexer = new Lexer(new SourceFile("..\\Compiler.Test\\parser_test_files\\prefix_operator.elsa"));
	auto parser = ElsaParser(lexer);
	auto exp = parser.parse_expression();

	if (auto poe = dynamic_cast<PrefixOperatorExpression*>(exp))
	{
		ASSERT_EQ(poe->get_operator(), TokenType::Exclamation);

		if (auto ie = dynamic_cast<IdentifierExpression*>(poe->get_right()))
		{
			ASSERT_EQ(ie->get_name(), L"my_var");
		}
		else
		{
			FAIL();
		}
	}
	else
	{
		FAIL();
	}
}