#include "avl_tree.hpp"
#include <gtest/gtest.h>

TEST(AVLTreeTest, Insert)
{
  ev::AVLTree<int> tree;
  EXPECT_TRUE(tree.insert(1));
  EXPECT_TRUE(tree.insert(2));
  EXPECT_TRUE(tree.insert(-1));
}

TEST(AVLTreeTest, Rotation)
{
  ev::AVLTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  EXPECT_EQ(tree.getRoot()->left->data, 1);
}
