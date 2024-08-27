#include "binary_search_tree.h"
#include <gtest/gtest.h>

TEST(BinarySearchTreeTest, Insertion)
{
  ev::BinarySearchTree<int> tree;
  EXPECT_TRUE(tree.insert(1).second);
  int x = 2;
  EXPECT_TRUE(tree.insert(x).second);

  int y = 3;
  EXPECT_TRUE(tree.insert(x + 2).second);
  EXPECT_EQ(tree.size(), 3);
}

TEST(BinarySearchTreeTest, FindMax)
{
  ev::BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.insert(7).second);
  ASSERT_TRUE(tree.insert(6).second);
  ASSERT_TRUE(tree.insert(3).second);
  ASSERT_TRUE(tree.insert(11).second);
  EXPECT_EQ(tree.findMax(), 11);
}

TEST(BinarySearchTreeTest, FindMin)
{
  ev::BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.insert(7).second);
  ASSERT_TRUE(tree.insert(6).second);
  ASSERT_TRUE(tree.insert(3).second);
  ASSERT_TRUE(tree.insert(11).second);
  ASSERT_TRUE(tree.insert(1).second);
  EXPECT_EQ(tree.findMin(), 1);
}

TEST(BinarySearchTreeTest, Contains)
{
  ev::BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.insert(7).second);
  ASSERT_TRUE(tree.insert(6).second);
  ASSERT_TRUE(tree.insert(3).second);
  ASSERT_TRUE(tree.insert(11).second);
  ASSERT_TRUE(tree.insert(1).second);
  EXPECT_TRUE(tree.contains(11));
  EXPECT_FALSE(tree.contains(42));
}

TEST(BinarySearchTreeTest, Remove)
{
  ev::BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.insert(7).second);
  ASSERT_TRUE(tree.insert(6).second);
  ASSERT_TRUE(tree.insert(3).second);
  ASSERT_TRUE(tree.insert(11).second);
  ASSERT_TRUE(tree.insert(1).second);
  EXPECT_NO_THROW(tree.remove(42));
  EXPECT_NO_THROW(tree.remove(11));
  EXPECT_FALSE(tree.contains(11));
}

TEST(BinarySearchTreeTest, Clear)
{
  ev::BinarySearchTree<int> tree;
  EXPECT_NO_THROW(tree.clear());
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.remove(2);
  EXPECT_NO_THROW(tree.clear());
  EXPECT_EQ(tree.size(), 0);
}

TEST(BinarySearchTreeTest, Size)
{
  ev::BinarySearchTree<int> tree;
  tree.insert(10);
  tree.insert(3);
  tree.insert(20);
  tree.insert(30);
  tree.insert(25);

  EXPECT_EQ(tree.size(), 5);
  tree.remove(20);
  EXPECT_EQ(tree.size(), 4);
  EXPECT_NO_THROW(tree.clear());
  EXPECT_EQ(tree.size(), 0);
}
