#include "lexer_test.h"

using namespace elsa;
using namespace elsa::compiler;

int lexer_test() { return 0; }

void get_tokens(Lexer& l, std::vector<std::unique_ptr<Token>>& t)
{
	auto next_token = l.next_token();
	while (next_token->get_type() != TokenType::END)
	{
		t.push_back(std::move(next_token));
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
	ASSERT_EQ(tokens[7]->get_type(), TokenType::BoolLiteral);
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

	ASSERT_EQ(tokens.size(), 32);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::Void);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[6]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[8]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[9]->get_type(), TokenType::StringLiteral);
	ASSERT_EQ(tokens[10]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[11]->get_type(), TokenType::RBracket);
	ASSERT_EQ(tokens[12]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[13]->get_type(), TokenType::Char);
	ASSERT_EQ(tokens[14]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[15]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[16]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[17]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[18]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[19]->get_type(), TokenType::CharLiteral);
	ASSERT_EQ(tokens[20]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[21]->get_type(), TokenType::RBracket);
	ASSERT_EQ(tokens[22]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[23]->get_type(), TokenType::Char);
	ASSERT_EQ(tokens[24]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[25]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[26]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[27]->get_type(), TokenType::LBracket);
	ASSERT_EQ(tokens[28]->get_type(), TokenType::Return);
	ASSERT_EQ(tokens[29]->get_type(), TokenType::CharLiteral);
	ASSERT_EQ(tokens[30]->get_type(), TokenType::Semicolon);
	ASSERT_EQ(tokens[31]->get_type(), TokenType::RBracket);
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

TEST(LexerTest, PROGRAM_8_MAX_MUNCH)
{
	auto lexer = Lexer(new SourceFile("..\\Compiler.Test\\lexing_test_files\\program8.elsa"));
	std::vector<std::unique_ptr<Token>> tokens;

	get_tokens(lexer, tokens);

	ASSERT_EQ(tokens.size(), 84);

	ASSERT_EQ(tokens[0]->get_type(), TokenType::Func);
	ASSERT_EQ(tokens[1]->get_type(), TokenType::Void);
	ASSERT_EQ(tokens[2]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[3]->get_type(), TokenType::LParen);
	ASSERT_EQ(tokens[4]->get_type(), TokenType::RParen);
	ASSERT_EQ(tokens[5]->get_type(), TokenType::LBracket);

	ASSERT_EQ(tokens[6]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[7]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[8]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[9]->get_type(), TokenType::BoolLiteral);
	ASSERT_EQ(tokens[10]->get_type(), TokenType::DoubleAmpersand);
	ASSERT_EQ(tokens[11]->get_type(), TokenType::BoolLiteral);
	ASSERT_EQ(tokens[12]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[13]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[14]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[15]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[16]->get_type(), TokenType::BoolLiteral);
	ASSERT_EQ(tokens[17]->get_type(), TokenType::DoubleVerticalBar);
	ASSERT_EQ(tokens[18]->get_type(), TokenType::BoolLiteral);
	ASSERT_EQ(tokens[19]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[20]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[21]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[22]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[23]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[24]->get_type(), TokenType::DoubleEquals);
	ASSERT_EQ(tokens[25]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[26]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[27]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[28]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[29]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[30]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[31]->get_type(), TokenType::PlusEquals);
	ASSERT_EQ(tokens[32]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[33]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[34]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[35]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[36]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[37]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[38]->get_type(), TokenType::MinusEquals);
	ASSERT_EQ(tokens[39]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[40]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[41]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[42]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[43]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[44]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[45]->get_type(), TokenType::AsterixEquals);
	ASSERT_EQ(tokens[46]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[47]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[48]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[49]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[50]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[51]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[52]->get_type(), TokenType::SlashEquals);
	ASSERT_EQ(tokens[53]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[54]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[55]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[56]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[57]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[58]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[59]->get_type(), TokenType::LessThanEquals);
	ASSERT_EQ(tokens[60]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[61]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[62]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[63]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[64]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[65]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[66]->get_type(), TokenType::GreaterThanEquals);
	ASSERT_EQ(tokens[67]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[68]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[69]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[70]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[71]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[72]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[73]->get_type(), TokenType::Ampersand);
	ASSERT_EQ(tokens[74]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[75]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[76]->get_type(), TokenType::Var);
	ASSERT_EQ(tokens[77]->get_type(), TokenType::Identifier);
	ASSERT_EQ(tokens[78]->get_type(), TokenType::Equals);
	ASSERT_EQ(tokens[79]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[80]->get_type(), TokenType::VerticalBar);
	ASSERT_EQ(tokens[81]->get_type(), TokenType::IntegerLiteral);
	ASSERT_EQ(tokens[82]->get_type(), TokenType::Semicolon);

	ASSERT_EQ(tokens[83]->get_type(), TokenType::RBracket);
}