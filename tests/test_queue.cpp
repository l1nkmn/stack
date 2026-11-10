#include <gtest/gtest.h>
#include "Queue.h"   // ваш заголовок с Queue
#include "List.h"

// ================== push_back ==================

TEST(QueueTest, PushBackToEmpty) {
    Queue<int> q;
    q.push_back(42);
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.pop_back(), 42);
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, PushBackMultiple) {
    Queue<int> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);

    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.pop_back(), 3);
    EXPECT_EQ(q.pop_back(), 2);
    EXPECT_EQ(q.pop_back(), 1);
    EXPECT_TRUE(q.isEmpty());
}

// ================== push_front ==================

TEST(QueueTest, PushFrontToEmpty) {
    Queue<int> q;
    q.push_front(10);
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.pop_front(), 10);
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, PushFrontMultiple) {
    Queue<int> q;
    q.push_front(1);
    q.push_front(2);
    q.push_front(3);

    // очередь после push_front: 3,2,1
    EXPECT_EQ(q.pop_front(), 3);
    EXPECT_EQ(q.pop_front(), 2);
    EXPECT_EQ(q.pop_front(), 1);
    EXPECT_TRUE(q.isEmpty());
}

// ================== Смешанные операции ==================

TEST(QueueTest, PushFrontAndPushBack) {
    Queue<int> q;
    q.push_back(2);   // [2]
    q.push_front(1);  // [1,2]
    q.push_back(3);   // [1,2,3]

    EXPECT_EQ(q.pop_front(), 1);
    EXPECT_EQ(q.pop_front(), 2);
    EXPECT_EQ(q.pop_front(), 3);
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, MixedPopBackAndPopFront) {
    Queue<int> q;
    q.push_back(1); // [1]
    q.push_back(2); // [1,2]
    q.push_back(3); // [1,2,3]

    EXPECT_EQ(q.pop_back(), 3);   // [1,2]
    EXPECT_EQ(q.pop_front(), 1);  // [2]
    EXPECT_EQ(q.pop_back(), 2);   // []
    EXPECT_TRUE(q.isEmpty());
}

// ================== isEmpty ==================

TEST(QueueTest, IsEmptyOnCreation) {
    Queue<int> q;
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, IsNotEmptyAfterPushBack) {
    Queue<int> q;
    q.push_back(5);
    EXPECT_FALSE(q.isEmpty());
}

TEST(QueueTest, IsNotEmptyAfterPushFront) {
    Queue<int> q;
    q.push_front(5);
    EXPECT_FALSE(q.isEmpty());
}

// ================== Разные типы ==================

TEST(QueueTest, WorksWithString) {
    Queue<std::string> q;
    q.push_back("hello");
    q.push_front("world");

    EXPECT_EQ(q.pop_front(), "world");
    EXPECT_EQ(q.pop_back(), "hello");
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, WorksWithDouble) {
    Queue<double> q;
    q.push_back(1.5);
    q.push_back(2.5);
    EXPECT_DOUBLE_EQ(q.pop_front(), 1.5);
    EXPECT_DOUBLE_EQ(q.pop_back(), 2.5);
}

TEST(QueueTest, WorksWithCustomType) {
    struct Point {
        int x, y;
        bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    };
    Queue<Point> q;
    q.push_back({1, 2});
    q.push_front({3, 4});

    EXPECT_EQ(q.pop_front(), (Point{3, 4}));
    EXPECT_EQ(q.pop_back(),  (Point{1, 2}));
}

// ================== Стресс ==================

TEST(QueueTest, ManyPushesBack) {
    Queue<int> q;
    const int N = 1000;
    for (int i = 0; i < N; ++i) q.push_back(i);

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.pop_front(), i);
    }
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, ManyPushesFront) {
    Queue<int> q;
    const int N = 1000;
    for (int i = 0; i < N; ++i) q.push_front(i);

    for (int i = N - 1; i >= 0; --i) {
        EXPECT_EQ(q.pop_front(), i);
    }
    EXPECT_TRUE(q.isEmpty());
}
