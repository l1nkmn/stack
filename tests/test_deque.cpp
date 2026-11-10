#include <gtest/gtest.h>
#include "Deque.h"
#include "List.h"

// ================== push_back ==================

TEST(DequeTest, PushBackToEmpty) {
    Deque<int> q;
    q.push_back(42);
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.pop_back(), 42);
    EXPECT_TRUE(q.isEmpty());
}

TEST(DequeTest, PushBackMultiple) {
    Deque<int> q;
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

TEST(DequeTest, PushFrontToEmpty) {
    Deque<int> q;
    q.push_front(10);
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.pop_front(), 10);
    EXPECT_TRUE(q.isEmpty());
}

TEST(DequeTest, PushFrontMultiple) {
    Deque<int> q;
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

TEST(DequeTest, PushFrontAndPushBack) {
    Deque<int> q;
    q.push_back(2);   // [2]
    q.push_front(1);  // [1,2]
    q.push_back(3);   // [1,2,3]

    EXPECT_EQ(q.pop_front(), 1);
    EXPECT_EQ(q.pop_front(), 2);
    EXPECT_EQ(q.pop_front(), 3);
    EXPECT_TRUE(q.isEmpty());
}

TEST(DequeTest, MixedPopBackAndPopFront) {
    Deque<int> q;
    q.push_back(1); // [1]
    q.push_back(2); // [1,2]
    q.push_back(3); // [1,2,3]

    EXPECT_EQ(q.pop_back(), 3);   // [1,2]
    EXPECT_EQ(q.pop_front(), 1);  // [2]
    EXPECT_EQ(q.pop_back(), 2);   // []
    EXPECT_TRUE(q.isEmpty());
}

// ================== isEmpty ==================

TEST(DequeTest, IsEmptyOnCreation) {
    Deque<int> q;
    EXPECT_TRUE(q.isEmpty());
}

TEST(DequeTest, IsNotEmptyAfterPushBack) {
    Deque<int> q;
    q.push_back(5);
    EXPECT_FALSE(q.isEmpty());
}

TEST(DequeTest, IsNotEmptyAfterPushFront) {
    Deque<int> q;
    q.push_front(5);
    EXPECT_FALSE(q.isEmpty());
}

// ================== Разные типы ==================

TEST(DequeTest, WorksWithString) {
    Deque<std::string> q;
    q.push_back("hello");
    q.push_front("world");

    EXPECT_EQ(q.pop_front(), "world");
    EXPECT_EQ(q.pop_back(), "hello");
    EXPECT_TRUE(q.isEmpty());
}

TEST(DequeTest, WorksWithDouble) {
    Deque<double> q;
    q.push_back(1.5);
    q.push_back(2.5);
    EXPECT_DOUBLE_EQ(q.pop_front(), 1.5);
    EXPECT_DOUBLE_EQ(q.pop_back(), 2.5);
}

TEST(DequeTest, WorksWithCustomType) {
    struct Point {
        int x, y;
        bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    };
    Deque<Point> q;
    q.push_back({1, 2});
    q.push_front({3, 4});

    EXPECT_EQ(q.pop_front(), (Point{3, 4}));
    EXPECT_EQ(q.pop_back(),  (Point{1, 2}));
}

// ================== Стресс ==================

TEST(DequeTest, ManyPushesBack) {
    Deque<int> q;
    const int N = 1000;
    for (int i = 0; i < N; ++i) q.push_back(i);

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.pop_front(), i);
    }
    EXPECT_TRUE(q.isEmpty());
}

TEST(DequeTest, ManyPushesFront) {
    Deque<int> q;
    const int N = 1000;
    for (int i = 0; i < N; ++i) q.push_front(i);

    for (int i = N - 1; i >= 0; --i) {
        EXPECT_EQ(q.pop_front(), i);
    }
    EXPECT_TRUE(q.isEmpty());
}
