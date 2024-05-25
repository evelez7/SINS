#include "binary_search_tree.h"
#include <gtest/gtest.h>

TEST(BinarySearchTreeTest, Insertion)
{
  BinarySearchTree<int> tree;
  EXPECT_TRUE(tree.insert(1));
  int x = 2;
  EXPECT_TRUE(tree.insert(x));

  int y = 3;
  EXPECT_TRUE(tree.insert(x + 2));
}

TEST(BinarySearchTreeTest, FindMax)
{
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.insert(7));
  ASSERT_TRUE(tree.insert(6));
  ASSERT_TRUE(tree.insert(3));
  ASSERT_TRUE(tree.insert(11));
  EXPECT_EQ(tree.findMax(), 11);
}

TEST(BinarySearchTreeTest, FindMin)
{
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.insert(7));
  ASSERT_TRUE(tree.insert(6));
  ASSERT_TRUE(tree.insert(3));
  ASSERT_TRUE(tree.insert(11));
  ASSERT_TRUE(tree.insert(1));
  EXPECT_EQ(tree.findMin(), 1);
}

TEST(BinarySearchTreeTest, Contains)
{
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.insert(7));
  ASSERT_TRUE(tree.insert(6));
  ASSERT_TRUE(tree.insert(3));
  ASSERT_TRUE(tree.insert(11));
  ASSERT_TRUE(tree.insert(1));
  EXPECT_TRUE(tree.contains(11));
  EXPECT_FALSE(tree.contains(42));
}

TEST(BinarySearchTreeTest, Remove)
{
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.insert(7));
  ASSERT_TRUE(tree.insert(6));
  ASSERT_TRUE(tree.insert(3));
  ASSERT_TRUE(tree.insert(11));
  ASSERT_TRUE(tree.insert(1));
  EXPECT_NO_THROW(tree.remove(42));
  EXPECT_NO_THROW(tree.remove(11));
  EXPECT_FALSE(tree.contains(11));
}
