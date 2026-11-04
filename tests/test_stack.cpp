#include <gtest/gtest.h>
#include "Stack.h"

TEST(StackTest, StartsEmpty) {
    Stack<int> s;
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, PushMakesNotEmpty) {
    Stack<int> s;
    int v = 10;
    s.push(v);
    EXPECT_FALSE(s.isEmpty());
}

TEST(StackTest, PopReturnsLastPushed) {
    Stack<int> s;
    int a = 1, b = 2, c = 3;
    s.push(a);
    s.push(b);
    s.push(c);

    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.pop(), 1);
}

TEST(StackTest, BecomesEmptyAfterPops) {
    Stack<int> s;
    int v = 5;
    s.push(v);
    s.pop();
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, CharStack) {
    Stack<char> s;
    char a = 'a', b = 'b';
    s.push(a);
    s.push(b);

    EXPECT_EQ(s.pop(), 'b');
    EXPECT_EQ(s.pop(), 'a');
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, DoubleStack) {
    Stack<double> s;
    double x = 1.5, y = 2.5;
    s.push(x);
    s.push(y);

    EXPECT_DOUBLE_EQ(s.pop(), 2.5);
    EXPECT_DOUBLE_EQ(s.pop(), 1.5);
}
