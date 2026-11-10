#include <gtest/gtest.h>
#include "Queue.h"
#include <string>

// ================== isEmpty ==================

TEST(QueueTest, IsEmptyOnCreation) {
    Queue<int> q;
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, IsNotEmptyAfterPush) {
    Queue<int> q;
    q.push(1);
    EXPECT_FALSE(q.isEmpty());
}

TEST(QueueTest, BecomesEmptyAfterPop) {
    Queue<int> q;
    q.push(1);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_TRUE(q.isEmpty());
}

// ================== FIFO: один элемент ==================

TEST(QueueTest, PushPopSingleElement) {
    Queue<int> q;
    q.push(42);
    EXPECT_EQ(q.pop(), 42);
    EXPECT_TRUE(q.isEmpty());
}

// ================== FIFO: порядок ==================

TEST(QueueTest, FifoOrder) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, FifoOrderInterleaved) {
    Queue<int> q;
    q.push(10);
    q.push(20);
    EXPECT_EQ(q.pop(), 10);   // осталась [20]

    q.push(30);               // [20, 30]
    q.push(40);               // [20, 30, 40]

    EXPECT_EQ(q.pop(), 20);
    EXPECT_EQ(q.pop(), 30);
    EXPECT_EQ(q.pop(), 40);
    EXPECT_TRUE(q.isEmpty());
}

// ================== Состояние после частичного опустошения ==================

TEST(QueueTest, SizeTrackingAfterPops) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_FALSE(q.isEmpty());
    q.pop();
    EXPECT_FALSE(q.isEmpty());
    q.pop();
    EXPECT_FALSE(q.isEmpty());
    q.pop();
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, CanReuseAfterEmpty) {
    Queue<int> q;
    q.push(1);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_TRUE(q.isEmpty());

    q.push(2);            // повторно используем
    q.push(3);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    EXPECT_TRUE(q.isEmpty());
}

// ================== Разные типы ==================

TEST(QueueTest, WorksWithString) {
    Queue<std::string> q;
    q.push("first");
    q.push("second");
    q.push("third");

    EXPECT_EQ(q.pop(), "first");
    EXPECT_EQ(q.pop(), "second");
    EXPECT_EQ(q.pop(), "third");
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, WorksWithDouble) {
    Queue<double> q;
    q.push(1.5);
    q.push(2.5);
    EXPECT_DOUBLE_EQ(q.pop(), 1.5);
    EXPECT_DOUBLE_EQ(q.pop(), 2.5);
}

TEST(QueueTest, WorksWithCustomType) {
    struct Point {
        int x, y;
        bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    };
    Queue<Point> q;
    q.push({1, 2});
    q.push({3, 4});
    q.push({5, 6});

    EXPECT_EQ(q.pop(), (Point{1, 2}));
    EXPECT_EQ(q.pop(), (Point{3, 4}));
    EXPECT_EQ(q.pop(), (Point{5, 6}));
}

// ================== Стресс ==================

TEST(QueueTest, ManyElementsFifo) {
    Queue<int> q;
    const int N = 1000;
    for (int i = 0; i < N; ++i) q.push(i);

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.pop(), i);
    }
    EXPECT_TRUE(q.isEmpty());
}
