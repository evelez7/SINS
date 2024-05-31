#include "set.hpp"
#include <gtest/gtest.h>

TEST(SetTest, Construction)
{
  EXPECT_NO_THROW(ev::set<int> s);
}

TEST(SetTest, Insert)
{
  ev::set<int> s;
  EXPECT_TRUE(s.insert(1));
}

TEST(SetTest, Clear)
{
  ev::set<int> s;
  s.insert(1);
  ASSERT_NO_THROW(s.clear());
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, Remove)
{
  ev::set<int> s;
  s.insert(10);
  s.insert(3);
  s.insert(20);
  s.insert(30);
  s.insert(25);
  EXPECT_NO_THROW(s.remove(25));
}
