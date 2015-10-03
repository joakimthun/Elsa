#include <gtest\gtest.h>
#include <vector>
#include <memory>

#include "lexing\lexer.h"

using namespace elsa;
using namespace elsa::compiler;

TEST(LexerTest, PROGRAM_1)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\test_files\\program1.elsa"));

	std::vector<std::unique_ptr<Token>> tokens;

	auto next_token = lexer.next_token();
	while (next_token->get_type() != TokenType::END)
	{
		tokens.push_back(std::unique_ptr<Token>(next_token));
		next_token = lexer.next_token();
	}

	ASSERT_EQ(tokens.size(), 17);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[6]->get_type(), TokenType::Comma);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[8]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[9]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[10]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[11]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[12]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[13]->get_type(), TokenType::Plus);
	ASSERT_EQ(tokens[14]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[15]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[16]->get_type(), TokenType::RBracket);
}