#include "lexer_test.h"

using namespace elsa;
using namespace elsa::compiler;

int lexer_test() { return 0; }

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
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program1.elsa"));
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

TEST(LexerTest, PROGRAM_2_INT_FUNC)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program2.elsa"));
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

TEST(LexerTest, PROGRAM_3_FLOAT_FUNC)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program3.elsa"));
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

TEST(LexerTest, PROGRAM_4_BOOL_FUNC)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program4.elsa"));
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

TEST(LexerTest, PROGRAM_5_STRUCT)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program5.elsa"));
	std::vector<std::unique_ptr<Token>> tokens;

	get_tokens(lexer, tokens);

	ASSERT_EQ(tokens.size(), 41);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Struct);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[6]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[8]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[9]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[10]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[11]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[12]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[13]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[14]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[15]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[16]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[17]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[18]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[19]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[20]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[21]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[22]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[23]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[24]->get_type(), TokenType::RBracket);
	ASSERT_EQ(tokens[25]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[26]->get_type(), TokenType::Void);
	ASSERT_EQ(tokens[27]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[28]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[29]->get_type(), TokenType::Int);
	ASSERT_EQ(tokens[30]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[31]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[32]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[33]->get_type(), TokenType::This);
	ASSERT_EQ(tokens[34]->get_type(), TokenType::Dot);
	ASSERT_EQ(tokens[35]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[36]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[37]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[38]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[39]->get_type(), TokenType::RBracket);
	ASSERT_EQ(tokens[40]->get_type(), TokenType::RBracket);
}

TEST(LexerTest, PROGRAM_6_STRINGS_AND_CHARS)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program6.elsa"));
	std::vector<std::unique_ptr<Token>> tokens;

	get_tokens(lexer, tokens);

	ASSERT_EQ(tokens.size(), 30);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::String);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[6]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::StringLiteral);
	ASSERT_EQ(tokens[8]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[9]->get_type(), TokenType::RBracket);
	ASSERT_EQ(tokens[10]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[11]->get_type(), TokenType::Char);
	ASSERT_EQ(tokens[12]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[13]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[14]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[15]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[16]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[17]->get_type(), TokenType::CharLiteral);
	ASSERT_EQ(tokens[18]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[19]->get_type(), TokenType::RBracket);
	ASSERT_EQ(tokens[20]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[21]->get_type(), TokenType::Char);
	ASSERT_EQ(tokens[22]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[23]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[24]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[25]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[26]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[27]->get_type(), TokenType::CharLiteral);
	ASSERT_EQ(tokens[28]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[29]->get_type(), TokenType::RBracket);
}

TEST(LexerTest, PROGRAM_7_MATH_EXPRESSION)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program7.elsa"));
	std::vector<std::unique_ptr<Token>> tokens;

	get_tokens(lexer, tokens);

	ASSERT_EQ(tokens.size(), 16);

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
	ASSERT_EQ(tokens[10]->get_type(), TokenType::Asterix);
	ASSERT_EQ(tokens[11]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[12]->get_type(), TokenType::Slash);
	ASSERT_EQ(tokens[13]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[14]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[15]->get_type(), TokenType::RBracket);
}