#include <gtest/gtest.h>
#include "vector.hpp"
#include <vector>

TEST(VectorTest, EqualSizeDefault) {
  ev::vector<int> test;
  std::vector<int> control;
  EXPECT_EQ(test.size(), control.size());
}

TEST(VectorTest, EqualSizeInitialized) {
  ev::vector<int> test(2);
  std::vector<int> control(2);
  EXPECT_EQ(test.size(), control.size());
}

TEST(VectorTest, PushBack) {
  ev::vector<int> test;
  test.push_back(1);
  EXPECT_EQ(test[0], 1);
  EXPECT_EQ(test.size(), 1);
  std::vector<int> control;
  control.push_back(1);
  EXPECT_EQ(test[0], control[0]);
  EXPECT_EQ(test.size(), control.size());
}

TEST(VectorTest, PopBack) {
  ev::vector<int> test;
  test.push_back(1);
  test.push_back(2);
  EXPECT_EQ(test[0], 1);
  EXPECT_EQ(test[1], 2);
  EXPECT_EQ(test.size(), 2);
  
  test.pop_back();
  EXPECT_EQ(test.size(), 1);
  EXPECT_EQ(test[0], 1);
}

TEST(VectorTest, Reserve) {
  ev::vector<int> test;
  test.reserve(100);
  EXPECT_EQ(test.capacity(), 100);
  EXPECT_EQ(test.size(), 0);
}

TEST(VectorTest, ReservePreexisting) {
  ev::vector<int> test;
  test.push_back(1);
  test.reserve(100);
  EXPECT_EQ(test.size(), 1);
  EXPECT_EQ(test.capacity(), 100);
}
