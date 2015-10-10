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

TEST(ParserTest, FUNC_DECLARATION)
{
	auto lexer = new Lexer(new SourceFile("..\\Compiler.Test\\parser_test_files\\func_declaration.elsa"));
	auto parser = ElsaParser(lexer);
	auto exp = parser.parse_statement();

	if (auto fde = dynamic_cast<FuncDeclarationExpression*>(exp))
	{
		ASSERT_EQ(fde->get_return_type()->get_type(), OType::Void);
		ASSERT_EQ(fde->get_name(), L"add");

		ASSERT_EQ(fde->get_body().size(), 2);
		ASSERT_EQ(fde->get_args().size(), 3);

		ASSERT_EQ(fde->get_args()[0]->get_name(), L"x");
		ASSERT_EQ(fde->get_args()[0]->get_type()->get_type(), OType::Int);

		ASSERT_EQ(fde->get_args()[1]->get_name(), L"y");
		ASSERT_EQ(fde->get_args()[1]->get_type()->get_type(), OType::Float);

		ASSERT_EQ(fde->get_args()[2]->get_name(), L"c");
		ASSERT_EQ(fde->get_args()[2]->get_type()->get_type(), OType::Char);

		if (auto vde1 = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[0].get()))
		{
			ASSERT_EQ(vde1->get_name(), L"x1");
			ASSERT_EQ(vde1->get_type(), L"int");

			if (auto ile = dynamic_cast<IntegerLiteralExpression*>(vde1->get_expression()))
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

		if (auto vde2 = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[1].get()))
		{
			ASSERT_EQ(vde2->get_name(), L"x2");
			ASSERT_EQ(vde2->get_type(), L"int");

			if (auto ble = dynamic_cast<BoolLiteralExpression*>(vde2->get_expression()))
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
	}
	else
	{
		FAIL();
	}
}