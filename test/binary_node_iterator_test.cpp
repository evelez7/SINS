#include "binary_node_iterator.hpp"
#include "binary_search_tree.h"
#include <cstdlib>
#include <gtest/gtest.h>

TEST(BinaryNodeIteratorTest, Constructor)
{
  ev::BinarySearchTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  auto it = tree.begin();
  EXPECT_EQ((*it).data, 1);
}

TEST(BinaryNodeIteratorTest, ArrowOperator)
{
  ev::BinarySearchTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  auto it = tree.begin();
  EXPECT_EQ(it->data, 1);
}

TEST(BinaryNodeIteratorTest, PreIncrement)
{
  ev::BinarySearchTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  auto it = tree.begin();
  EXPECT_EQ((*it).data, 1);
  ++it;
  EXPECT_EQ((*it).data, 2);
  ++it;
  EXPECT_EQ((*it).data, 3);
}

TEST(BinaryNodeIteratorTest, PreDecrement)
{
  ev::BinarySearchTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  auto it = tree.begin();
  ++it;
  ++it;
  EXPECT_EQ((*it).data, 3);
  --it;
  EXPECT_EQ((*it).data, 2);
  --it;
  EXPECT_EQ((*it).data, 1);
}
