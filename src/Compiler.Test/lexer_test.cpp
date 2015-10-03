#include <gtest\gtest.h>
#include <vector>
#include <memory>

#include "lexing\lexer.h"

using namespace elsa;
using namespace elsa::compiler;

void get_tokens(Lexer& l, std::vector<std::unique_ptr<Token>>& t)
{
	auto next_token = l.next_token();
	while (next_token->get_type() != TokenType::END)
	{
		t.push_back(std::unique_ptr<Token>(next_token));
		next_token = l.next_token();
	}
}

TEST(LexerTest, PROGRAM_1_FUNC)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\test_files\\program1.elsa"));
	std::vector<std::unique_ptr<Token>> tokens;

	get_tokens(lexer, tokens);

	ASSERT_EQ(tokens.size(), 17);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[6]->get_type(), TokenType::Comma);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::Int);
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

TEST(LexerTest, PROGRAM_2_INTS)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\test_files\\program2.elsa"));
	std::vector<std::unique_ptr<Token>> tokens;

	get_tokens(lexer, tokens);

	ASSERT_EQ(tokens.size(), 12);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[6]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[8]->get_type(), TokenType::Plus);
	ASSERT_EQ(tokens[9]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[10]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[11]->get_type(), TokenType::RBracket);
}

TEST(LexerTest, PROGRAM_3_FLOATS)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\test_files\\program3.elsa"));
	std::vector<std::unique_ptr<Token>> tokens;

	get_tokens(lexer, tokens);

	ASSERT_EQ(tokens.size(), 12);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::Float);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[6]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::FloatLiteral);
	ASSERT_EQ(tokens[8]->get_type(), TokenType::Plus);
	ASSERT_EQ(tokens[9]->get_type(), TokenType::FloatLiteral);
	ASSERT_EQ(tokens[10]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[11]->get_type(), TokenType::RBracket);
}

TEST(LexerTest, PROGRAM_4_BOOL)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\test_files\\program4.elsa"));
	std::vector<std::unique_ptr<Token>> tokens;

	get_tokens(lexer, tokens);

	ASSERT_EQ(tokens.size(), 10);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::Bool);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[6]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::True);
	ASSERT_EQ(tokens[8]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[9]->get_type(), TokenType::RBracket);
}