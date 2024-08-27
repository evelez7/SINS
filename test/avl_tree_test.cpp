#include "avl_tree.hpp"
#include "binary_node_iterator.hpp"
#include <gtest/gtest.h>

TEST(AVLTreeTest, Insert)
{
  ev::AVLTree<int> tree;
  EXPECT_TRUE(tree.insert(1).second);
  EXPECT_EQ(tree.getRoot()->data, 1);
  EXPECT_TRUE(tree.insert(2).second);
  EXPECT_EQ(tree.getRoot()->right->data, 2);
  EXPECT_TRUE(tree.insert(-1).second);
  EXPECT_EQ(tree.getRoot()->left->data, -1);
}

TEST(AVLTreeTest, Clear)
{
  ev::AVLTree<int> tree;
  EXPECT_TRUE(tree.insert(1).second);
  EXPECT_TRUE(tree.insert(2).second);
  EXPECT_TRUE(tree.insert(-1).second);

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
  EXPECT_EQ(tree.getRoot()->data, 2);
  EXPECT_EQ(tree.getRoot()->right->data, 3);
  tree.insert(4);
  tree.insert(5);
  EXPECT_EQ(tree.getRoot()->right->data, 4);
  EXPECT_EQ(tree.getRoot()->right->right->data, 5);
  EXPECT_EQ(tree.getRoot()->right->left->data, 3);
  tree.remove(2);
  EXPECT_EQ(tree.getRoot()->data, 4);
  EXPECT_EQ(tree.getRoot()->left->data, 1);
  EXPECT_EQ(tree.getRoot()->left->right->data, 3);
  EXPECT_EQ(tree.getRoot()->right->data, 5);
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

TEST(AVLTreeTest, Size)
{
  ev::AVLTree<int> tree;
  tree.insert(10);
  tree.insert(3);
  tree.insert(20);
  tree.insert(30);
  tree.insert(25);

  EXPECT_EQ(tree.size(), 5);
  tree.remove(20);
  EXPECT_EQ(tree.size(), 4);
  tree.clear();
  EXPECT_EQ(tree.size(), 0);
}

TEST(AVLTreeTest, Remove)
{
  ev::AVLTree<int> tree;
  tree.insert(10);
  tree.insert(3);
  tree.insert(20);
  tree.insert(30);
  tree.insert(25);

  tree.remove(20);
  tree.remove(20);
  EXPECT_EQ(tree.getRoot()->right->data, 25);
  EXPECT_EQ(tree.size(), 4);
  tree.clear();
}

TEST(AVLTreeTest, Balance)
{
  ev::AVLTree<int> tree;
  tree.insert(41);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(32);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(7);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(21);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(68);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(70);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(95);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(73);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(86);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(40);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(16);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(22);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(87);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(6);
  EXPECT_TRUE(tree.checkBalance());
  tree.insert(26);
  EXPECT_TRUE(tree.checkBalance());
  tree.remove(6);
  EXPECT_TRUE(tree.checkBalance());
  tree.remove(40);
  EXPECT_TRUE(tree.checkBalance());
  tree.remove(73);
  EXPECT_TRUE(tree.checkBalance());
  tree.remove(tree.getRoot()->data);
  EXPECT_TRUE(tree.checkBalance());
}
