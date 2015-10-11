#include "parser_test.h"

using namespace elsa;
using namespace elsa::compiler;

int parser_test() { return 0; }

template<typename TExpression, typename TValue>
void assert_is_literal_expression(Expression* exp, TValue value)
{
	if (auto e = dynamic_cast<TExpression*>(exp))
	{
		ASSERT_EQ(e->get_value(), value);

	}
	else
	{
		FAIL();
	}
}

BinaryOperatorExpression* assert_is_binary_operator_expression(Expression* exp, TokenType op)
{
	if (auto boe = dynamic_cast<BinaryOperatorExpression*>(exp))
	{
		EXPECT_EQ(boe->get_operator(), op);
		return boe;
	}

	return nullptr;
}

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

		assert_is_literal_expression<IntegerLiteralExpression, int>(vde->get_expression(), 10);
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

		assert_is_literal_expression<FloatLiteralExpression, float>(vde->get_expression(), 10.0f);
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

		assert_is_literal_expression<StringLiteralExpression, std::wstring>(vde->get_expression(), L"Hello World!");
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

		assert_is_literal_expression<BoolLiteralExpression, bool>(vde->get_expression(), true);
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

		assert_is_literal_expression<BoolLiteralExpression, bool>(vde->get_expression(), false);
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

		assert_is_literal_expression<CharLiteralExpression, wchar_t>(vde->get_expression(), L'X');
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

			assert_is_literal_expression<IntegerLiteralExpression, int>(vde1->get_expression(), 10);
		}
		else
		{
			FAIL();
		}

		if (auto vde2 = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[1].get()))
		{
			ASSERT_EQ(vde2->get_name(), L"x2");
			ASSERT_EQ(vde2->get_type(), L"int");

			assert_is_literal_expression<BoolLiteralExpression, bool>(vde2->get_expression(), false);
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

TEST(ParserTest, PRECEDENCE)
{
	auto lexer = new Lexer(new SourceFile("..\\Compiler.Test\\parser_test_files\\precedence.elsa"));
	auto parser = ElsaParser(lexer);

	auto exp1 = parser.parse_expression();
	if (auto vde1 = dynamic_cast<VariableDeclarationExpression*>(exp1))
	{
		ASSERT_EQ(vde1->get_name(), L"x1");
		ASSERT_EQ(vde1->get_type(), L"int");

		if (auto boe = assert_is_binary_operator_expression(vde1->get_expression(), TokenType::Plus))
		{
			assert_is_literal_expression<IntegerLiteralExpression, int>(boe->get_left(), 1);
			assert_is_literal_expression<IntegerLiteralExpression, int>(boe->get_right(), 2);
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
	if (auto vde2 = dynamic_cast<VariableDeclarationExpression*>(exp2))
	{
		ASSERT_EQ(vde2->get_name(), L"x2");
		ASSERT_EQ(vde2->get_type(), L"int");

		if (auto boe = assert_is_binary_operator_expression(vde2->get_expression(), TokenType::Plus))
		{
			assert_is_literal_expression<IntegerLiteralExpression, int>(boe->get_left(), 1);

			if (auto boe2 = assert_is_binary_operator_expression(boe->get_right(), TokenType::Asterix))
			{
				assert_is_literal_expression<IntegerLiteralExpression, int>(boe2->get_left(), 2);
				assert_is_literal_expression<IntegerLiteralExpression, int>(boe2->get_right(), 5);
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