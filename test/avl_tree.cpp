#include "avl_tree.hpp"
#include <gtest/gtest.h>

TEST(AVLTreeTest, Insert)
{
  ev::AVLTree<int> tree;
  EXPECT_TRUE(tree.insert(1));
  EXPECT_TRUE(tree.insert(2));
  EXPECT_TRUE(tree.insert(-1));
}
