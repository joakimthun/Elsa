#include <gtest\gtest.h>

#include "lexing\lexer.h"

using namespace elsa;
using namespace elsa::compiler;

class LexerTest : public testing::Test {
protected:
	virtual void SetUp()
	{

	}

	virtual void TearDown() {}

	Lexer lexer_;
};

TEST_F(LexerTest, DUMMY)
{
	ASSERT_EQ(1, 1);
}