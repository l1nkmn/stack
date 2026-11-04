#include <gtest/gtest.h>
#include <map>
#include <string>
#include "TArithmeticExpression.h"

// ---------- Перевод в постфиксную ----------

TEST(ArithmeticTest, SimpleAddition) {
    TArithmeticExpression e;
    int err = e.setInfix("a + b");
    EXPECT_EQ(err, 0);
    EXPECT_EQ(e.getPostfix(), "a b +");
}

TEST(ArithmeticTest, Priority) {
    TArithmeticExpression e;
    int err = e.setInfix("a + b * c");
    EXPECT_EQ(err, 0);
    EXPECT_EQ(e.getPostfix(), "a b c * +");
}

TEST(ArithmeticTest, Parentheses) {
    TArithmeticExpression e;
    int err = e.setInfix("(a + b) * c");
    EXPECT_EQ(err, 0);
    EXPECT_EQ(e.getPostfix(), "a b + c *");
}

TEST(ArithmeticTest, NestedParentheses) {
    TArithmeticExpression e;
    int err = e.setInfix("a * (b + (c - d))");
    EXPECT_EQ(err, 0);
    EXPECT_EQ(e.getPostfix(), "a b c d - + *");
}

TEST(ArithmeticTest, SubtractionLeftAssoc) {
    TArithmeticExpression e;
    int err = e.setInfix("a - b - c");
    EXPECT_EQ(err, 0);
    EXPECT_EQ(e.getPostfix(), "a b - c -");
}

TEST(ArithmeticTest, UnbalancedOpen) {
    TArithmeticExpression e;
    int err = e.setInfix("a + (b * c");
    EXPECT_NE(err, 0);
}

TEST(ArithmeticTest, UnbalancedClose) {
    TArithmeticExpression e;
    int err = e.setInfix("a + b) * c");
    EXPECT_NE(err, 0);
}

TEST(ArithmeticTest, BadCharacter) {
    TArithmeticExpression e;
    int err = e.setInfix("a + $");
    EXPECT_NE(err, 0);
}

// ---------- Вычисление ----------

TEST(ArithmeticEvalTest, SimpleValues) {
    TArithmeticExpression e;
    ASSERT_EQ(e.setInfix("a + b * c"), 0);

    std::map<char, double> vars;
    vars['a'] = 2;
    vars['b'] = 3;
    vars['c'] = 4;

    double res = 0;
    int err = e.calc(vars, res);
    EXPECT_EQ(err, 0);
    EXPECT_DOUBLE_EQ(res, 14.0); // 2 + 3*4
}

TEST(ArithmeticEvalTest, ParenthesesEval) {
    TArithmeticExpression e;
    ASSERT_EQ(e.setInfix("(a + b) * (c - d)"), 0);

    std::map<char, double> vars;
    vars['a'] = 1;
    vars['b'] = 2;
    vars['c'] = 10;
    vars['d'] = 4;

    double res = 0;
    EXPECT_EQ(e.calc(vars, res), 0);
    EXPECT_DOUBLE_EQ(res, 18.0); // 3 * 6
}

TEST(ArithmeticEvalTest, SubtractionAndDivision) {
    TArithmeticExpression e;
    ASSERT_EQ(e.setInfix("a - b / c"), 0);

    std::map<char, double> vars;
    vars['a'] = 10;
    vars['b'] = 8;
    vars['c'] = 4;

    double res = 0;
    EXPECT_EQ(e.calc(vars, res), 0);
    EXPECT_DOUBLE_EQ(res, 8.0); // 10 - 2
}

TEST(ArithmeticEvalTest, MissingVariable) {
    TArithmeticExpression e;
    ASSERT_EQ(e.setInfix("a + b"), 0);

    std::map<char, double> vars;
    vars['a'] = 5;  // b не задана

    double res = 0;
    int err = e.calc(vars, res);
    EXPECT_NE(err, 0);
}

TEST(ArithmeticEvalTest, DivisionByZero) {
    TArithmeticExpression e;
    ASSERT_EQ(e.setInfix("a / b"), 0);

    std::map<char, double> vars;
    vars['a'] = 10;
    vars['b'] = 0;

    double res = 0;
    int err = e.calc(vars, res);
    EXPECT_NE(err, 0);
}

TEST(ArithmeticEvalTest, SingleVariable) {
    TArithmeticExpression e;
    ASSERT_EQ(e.setInfix("x"), 0);

    std::map<char, double> vars;
    vars['x'] = 42.0;

    double res = 0;
    EXPECT_EQ(e.calc(vars, res), 0);
    EXPECT_DOUBLE_EQ(res, 42.0);
}
