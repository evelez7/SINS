#include "avl_tree.hpp"
#include <gtest/gtest.h>

TEST(AVLTreeTest, Insert)
{
  ev::AVLTree<int> tree;
  EXPECT_TRUE(tree.insert(1));
  EXPECT_TRUE(tree.insert(2));
  EXPECT_TRUE(tree.insert(-1));
}

TEST(AVLTreeTest, Clear)
{
  ev::AVLTree<int> tree;
  EXPECT_TRUE(tree.insert(1));
  EXPECT_TRUE(tree.insert(2));
  EXPECT_TRUE(tree.insert(-1));

  ASSERT_NO_THROW(tree.clear());
  EXPECT_EQ(tree.getRoot(), nullptr);
}

TEST(AVLTreeTest, Rotation)
{
  ev::AVLTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  EXPECT_EQ(tree.getRoot()->left->data, 1);
}

TEST(AVLTreeTest, HeightCheck)
{
  ev::AVLTree<int> tree;
  tree.insert(10);
  tree.insert(3);
  tree.insert(20);
  tree.insert(30);
  tree.insert(25);

  EXPECT_EQ(tree.getRoot()->height, 3);
  EXPECT_EQ(tree.getRoot()->left->height, 1);
  EXPECT_EQ(tree.getRoot()->right->height, 2);
  EXPECT_EQ(tree.getRoot()->right->left->height, 1);
}
