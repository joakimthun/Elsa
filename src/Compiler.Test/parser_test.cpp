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

BinaryOperatorExpression* assert_is_binary_operator_expression(Expression* exp, elsa::compiler::TokenType op)
{
	if (auto boe = dynamic_cast<BinaryOperatorExpression*>(exp))
	{
		EXPECT_EQ(boe->get_operator(), op);
		return boe;
	}

	return nullptr;
}

TEST(ParserTest, VARIABLE_DECLARATION)
{
	auto lexer = new Lexer(new SourceFile(L"..\\Compiler.Test\\parser_test_files\\variable_declaration.elsa"));
	auto parser = ElsaParser(lexer, false);
	auto exp = parser.parse_statement();

	if (auto fde = dynamic_cast<FuncDeclarationExpression*>(exp.get()))
	{
		if (auto vde = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[0].get()))
		{
			ASSERT_EQ(vde->get_name(), L"var1");
			ASSERT_EQ(vde->get_type()->get_type(), ObjectType::Bool);

			if (auto poe = dynamic_cast<PrefixOperatorExpression*>(vde->get_expression()))
			{
				ASSERT_EQ(poe->get_operator(), TokenType::Exclamation);

				if (auto ble = dynamic_cast<BoolLiteralExpression*>(poe->get_right()))
				{
					ASSERT_EQ(ble->get_value(), false);
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
	else
	{
		FAIL();
	}
}

TEST(ParserTest, LITERALS)
{
	auto lexer = new Lexer(new SourceFile(L"..\\Compiler.Test\\parser_test_files\\literals.elsa"));
	auto parser = ElsaParser(lexer, false);

	auto exp = parser.parse_statement();

	if (auto fde = dynamic_cast<FuncDeclarationExpression*>(exp.get()))
	{
		if (auto vde = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[0].get()))
		{
			ASSERT_EQ(vde->get_name(), L"x1");
			ASSERT_EQ(vde->get_type()->get_type(), ObjectType::Int);

			assert_is_literal_expression<IntegerLiteralExpression, int>(vde->get_expression(), 10);
		}
		else
		{
			FAIL();
		}

		if (auto vde = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[1].get()))
		{
			ASSERT_EQ(vde->get_name(), L"x2");
			ASSERT_EQ(vde->get_type()->get_type(), ObjectType::Float);

			assert_is_literal_expression<FloatLiteralExpression, float>(vde->get_expression(), 10.0f);
		}
		else
		{
			FAIL();
		}

		if (auto vde = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[2].get()))
		{
			ASSERT_EQ(vde->get_name(), L"x3");
			ASSERT_EQ(vde->get_type()->get_type(), ObjectType::Bool);

			assert_is_literal_expression<BoolLiteralExpression, bool>(vde->get_expression(), true);
		}
		else
		{
			FAIL();
		}

		if (auto vde = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[3].get()))
		{
			ASSERT_EQ(vde->get_name(), L"x4");
			ASSERT_EQ(vde->get_type()->get_type(), ObjectType::Bool);

			assert_is_literal_expression<BoolLiteralExpression, bool>(vde->get_expression(), false);
		}
		else
		{
			FAIL();
		}

		if (auto vde = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[4].get()))
		{
			ASSERT_EQ(vde->get_name(), L"x5");
			ASSERT_EQ(vde->get_type()->get_type(), ObjectType::Char);

			assert_is_literal_expression<CharLiteralExpression, wchar_t>(vde->get_expression(), L'X');
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
	auto lexer = new Lexer(new SourceFile(L"..\\Compiler.Test\\parser_test_files\\func_declaration.elsa"));
	auto parser = ElsaParser(lexer, false);
	auto exp = parser.parse_statement();

	if (auto fde = dynamic_cast<FuncDeclarationExpression*>(exp.get()))
	{
		ASSERT_EQ(fde->get_return_type()->get_type(), ObjectType::Void);
		ASSERT_EQ(fde->get_name(), L"add");

		ASSERT_EQ(fde->get_body().size(), 2);
		ASSERT_EQ(fde->get_args().size(), 3);

		ASSERT_EQ(fde->get_args()[0]->get_name(), L"x");
		ASSERT_EQ(fde->get_args()[0]->get_type()->get_type(), ObjectType::Int);

		ASSERT_EQ(fde->get_args()[1]->get_name(), L"y");
		ASSERT_EQ(fde->get_args()[1]->get_type()->get_type(), ObjectType::Float);

		ASSERT_EQ(fde->get_args()[2]->get_name(), L"c");
		ASSERT_EQ(fde->get_args()[2]->get_type()->get_type(), ObjectType::Char);

		if (auto vde1 = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[0].get()))
		{
			ASSERT_EQ(vde1->get_name(), L"x1");
			ASSERT_EQ(vde1->get_type()->get_type(), ObjectType::Int);

			assert_is_literal_expression<IntegerLiteralExpression, int>(vde1->get_expression(), 10);
		}
		else
		{
			FAIL();
		}

		if (auto vde2 = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[1].get()))
		{
			ASSERT_EQ(vde2->get_name(), L"x2");
			ASSERT_EQ(vde2->get_type()->get_type(), ObjectType::Bool);

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
	auto lexer = new Lexer(new SourceFile(L"..\\Compiler.Test\\parser_test_files\\precedence.elsa"));
	auto parser = ElsaParser(lexer, false);

	auto exp = parser.parse_statement();

	if (auto fde = dynamic_cast<FuncDeclarationExpression*>(exp.get()))
	{
		if (auto vde1 = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[0].get()))
		{
			ASSERT_EQ(vde1->get_name(), L"x1");
			ASSERT_EQ(vde1->get_type()->get_type(), ObjectType::Int);

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

		if (auto vde2 = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[1].get()))
		{
			ASSERT_EQ(vde2->get_name(), L"x2");
			ASSERT_EQ(vde2->get_type()->get_type(), ObjectType::Int);

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

		if (auto vde3 = dynamic_cast<VariableDeclarationExpression*>(fde->get_body()[2].get()))
		{
			ASSERT_EQ(vde3->get_name(), L"x3");
			ASSERT_EQ(vde3->get_type()->get_type(), ObjectType::Int);

			if (auto boe = assert_is_binary_operator_expression(vde3->get_expression(), TokenType::Plus))
			{
				if (auto boe2 = assert_is_binary_operator_expression(boe->get_left(), TokenType::Minus))
				{
					assert_is_literal_expression<IntegerLiteralExpression, int>(boe2->get_left(), 1);

					if (auto boe3 = assert_is_binary_operator_expression(boe2->get_right(), TokenType::Slash))
					{
						assert_is_literal_expression<IntegerLiteralExpression, int>(boe3->get_left(), 10);
						assert_is_literal_expression<IntegerLiteralExpression, int>(boe3->get_right(), 2);
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

				if (auto boe4 = assert_is_binary_operator_expression(boe->get_right(), TokenType::Asterix))
				{
					assert_is_literal_expression<IntegerLiteralExpression, int>(boe4->get_left(), 5);
					assert_is_literal_expression<IntegerLiteralExpression, int>(boe4->get_right(), 10);
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
	else
	{
		FAIL();
	}
}

TEST(ParserTest, STRUCT)
{
	auto lexer = new Lexer(new SourceFile(L"..\\Compiler.Test\\parser_test_files\\struct.elsa"));
	auto parser = ElsaParser(lexer, false);

	auto exp1 = parser.parse_statement();
	if (auto str_exp = dynamic_cast<StructDeclarationExpression*>(exp1.get()))
	{
		ASSERT_EQ(L"Test", str_exp->get_name());
	}
	else
	{
		FAIL();
	}
}