#include "gtest/gtest.h"
#include <bits/stdint-intn.h>

#include "rlc/ast/Call.hpp"
#include "rlc/parser/Lexer.hpp"
#include "rlc/parser/Parser.hpp"
#include "rlc/utils/ScopeGuard.hpp"

using namespace rlc;

TEST(ParserTest, testScalarConstantExpressions)
{
	Parser p("3", "fileName");

	auto exp = p.primaryExpression();
	if (!exp)
		FAIL();

	EXPECT_TRUE(exp->isA<ScalarConstant>());
	EXPECT_EQ(3, exp->get<ScalarConstant>().get<int64_t>());
}

TEST(ParserTest, testScalarBoolExpressions)
{
	Parser p("true", "fileName");

	auto exp = p.primaryExpression();
	if (!exp)
		FAIL();

	EXPECT_TRUE(exp->isA<ScalarConstant>());
	EXPECT_EQ(true, exp->get<ScalarConstant>().get<bool>());
}

TEST(ParserTest, testScalarDoubleExpressions)
{
	Parser p("3.14", "fileName");

	auto exp = p.primaryExpression();
	if (!exp)
		FAIL();

	EXPECT_TRUE(exp->isA<ScalarConstant>());
	EXPECT_EQ(3.14, exp->get<ScalarConstant>().get<double>());
}

TEST(ParserTest, testExpression)
{
	Parser p("3.14", "fileName");

	auto exp = p.expression();
	if (!exp)
		FAIL();

	EXPECT_TRUE(exp->isA<ScalarConstant>());
	EXPECT_EQ(3.14, exp->get<ScalarConstant>().get<double>());
}

TEST(ParserTest, testAdditiveExpression)
{
	Parser p("3.14 + 2", "fileName");

	auto exp = p.expression();
	if (!exp)
		FAIL();

	EXPECT_TRUE(exp->isA<Call>());
	EXPECT_EQ(exp->getCall().argsCount(), 2);
}
