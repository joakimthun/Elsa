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

TEST(ParserTest, VARIABLE_DECLARATION)
{
	auto lexer = new Lexer(new SourceFile("..\\Compiler.Test\\parser_test_files\\variable_declaration.elsa"));
	auto parser = ElsaParser(lexer);
	auto exp = parser.parse_expression();

	if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp))
	{
		ASSERT_EQ(vde->get_name(), L"var1");
		ASSERT_EQ(vde->get_type(), L"int");

		if (auto poe = dynamic_cast<PrefixOperatorExpression*>(vde->get_expression()))
		{
			ASSERT_EQ(poe->get_operator(), TokenType::Exclamation);

			if (auto ie = dynamic_cast<IdentifierExpression*>(poe->get_right()))
			{
				ASSERT_EQ(ie->get_name(), L"var2");
			}
			else
			{
				FAIL();
			}
		}
	}
	else
	{
		FAIL();
	}
}

TEST(ParserTest, LITERALS)
{
	auto lexer = new Lexer(new SourceFile("..\\Compiler.Test\\parser_test_files\\literals.elsa"));
	auto parser = ElsaParser(lexer);

	auto exp = parser.parse_expression();
	if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp))
	{
		ASSERT_EQ(vde->get_name(), L"x");
		ASSERT_EQ(vde->get_type(), L"int");

		if (auto ile = dynamic_cast<IntegerLiteralExpression*>(vde->get_expression()))
		{
			ASSERT_EQ(ile->get_value(), 10);
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

	auto exp2 = parser.parse_expression();
	if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp2))
	{
		ASSERT_EQ(vde->get_name(), L"x");
		ASSERT_EQ(vde->get_type(), L"int");

		if (auto fle = dynamic_cast<FloatLiteralExpression*>(vde->get_expression()))
		{
			ASSERT_FLOAT_EQ(fle->get_value(), 10.0f);
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

	auto exp3 = parser.parse_expression();
	if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp3))
	{
		ASSERT_EQ(vde->get_name(), L"x");
		ASSERT_EQ(vde->get_type(), L"int");

		if (auto sle = dynamic_cast<StringLiteralExpression*>(vde->get_expression()))
		{
			ASSERT_EQ(sle->get_value(), L"Hello World!");
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

	auto exp4 = parser.parse_expression();
	if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp4))
	{
		ASSERT_EQ(vde->get_name(), L"x");
		ASSERT_EQ(vde->get_type(), L"int");

		if (auto ble = dynamic_cast<BoolLiteralExpression*>(vde->get_expression()))
		{
			ASSERT_EQ(ble->get_value(), true);
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

	auto exp5 = parser.parse_expression();
	if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp5))
	{
		ASSERT_EQ(vde->get_name(), L"x");
		ASSERT_EQ(vde->get_type(), L"int");

		if (auto ble = dynamic_cast<BoolLiteralExpression*>(vde->get_expression()))
		{
			ASSERT_EQ(ble->get_value(), false);
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

	auto exp6 = parser.parse_expression();
	if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp6))
	{
		ASSERT_EQ(vde->get_name(), L"x");
		ASSERT_EQ(vde->get_type(), L"int");

		if (auto cle = dynamic_cast<CharLiteralExpression*>(vde->get_expression()))
		{
			ASSERT_EQ(cle->get_value(), L'X');
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