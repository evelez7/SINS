#include "map.hpp"
#include <gtest/gtest.h>

TEST(MapTest, Insertion)
{
  ev::map<int, int> map;
  EXPECT_TRUE(map.insert(1, 2).second);
  EXPECT_TRUE(map.insert(2, 3).second);
  EXPECT_EQ(map.size(), 2);
}
