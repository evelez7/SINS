#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <utility>

template <typename T> class BinarySearchTree
{
  struct Node
  {
    T data;
    Node *left;
    Node *right;

    Node(const T &data, Node *left, Node *right)
        : data(data), left(left), right(right)
    {
    }
  };

  Node *root;

  bool insert(const T &toInsert, Node *&node)
  {
    if (!node)
    {
      node = new Node(toInsert, nullptr, nullptr);
      return true;
    }
    else if (toInsert < node->data)
      return insert(toInsert, node->left);
    else if (toInsert > node->data)
      return insert(toInsert, node->right);
    return false;
  }

  bool contains(const T &toFind, Node *&node)
  {
    if (!node)
      return false;
    else if (toFind < node->data)
      return contains(toFind, node->left);
    else if (toFind > node->data)
      return contains(toFind, node->right);
    return true;
  }

  Node *findMin(Node *node) const
  {
    if (node == nullptr)
      return nullptr;
    if (node->left == nullptr)
      return node;
    return findMin(node->left);
  }

  Node *findMax(Node *node) const
  {
    if (node == nullptr)
      return nullptr;
    if (node->right == nullptr)
      return node;
    return findMax(node->right);
  }

public:
  BinarySearchTree() : root(nullptr) {}

  bool insert(const T &toInsert)
  {
    return insert(toInsert, root);
  }

  bool contains(const T &toFind)
  {
    return contains(toFind, root);
  }

  const T &findMin() const
  {
    return findMin(root)->data;
  }

  const T &findMax() const
  {
    return findMax(root)->data;
  }
};

#endif
