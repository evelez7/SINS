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
}
