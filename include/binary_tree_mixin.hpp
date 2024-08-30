#ifndef EV_TREE_MIXIN_HPP
#define EV_TREE_MIXIN_HPP

#include "binary_node_iterator.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>

namespace ev
{
template<typename T, typename NodeType> class AVLTree;
template<typename T> class BinarySearchTree;

/// Base class for all binary trees (BST, AVL, etc)
/// Contains common functions for all binary trees
template<typename T, typename N> class BinaryTree
{
protected:
  N *root;
  std::size_t n;

  void clear(N *&node)
  {
    if (!node)
      return;
    if (node->left)
      clear(node->left);
    if (node->right)
      clear(node->right);
    delete node;
    node = nullptr;
  }

  std::pair<N *, N *> search(const T &toFind, N *node) const
  {
    N *parent = nullptr;
    while (node)
    {
      if (toFind == node->data)
        return {node, parent};
      else if (toFind < node->data)
      {
        parent = node;
        node = node->left;
      }
      else
      {
        parent = node;
        node = node->right;
      }
    }
    return {nullptr, parent};
  }

  N *findMin(N *node) const
  {
    if (!node)
      return nullptr;
    if (!node->left)
      return node;
    return findMin(node->left);
  }

  N *findMax(N *node) const
  {
    if (!node)
      return nullptr;
    if (!node->right)
      return node;
    return findMax(node->right);
  }

  N *removeNode(N *&node)
  {
    if (node->left && node->right)
    {
      node->data = findMin(node->right)->data;
      node->right = removeHelper(node->data, node->right);
    }
    else
    {
      N *old = node;
      node = (node->left != nullptr) ? node->left : node->right;
      delete old;
      --n;
    }
    return node;
  }

  N* removeHelper(const T&toRemove, N*node)
  {
    if (!node)
      return nullptr;
    if (toRemove < node->data)
      node->left = removeHelper(toRemove, node->left);
    else if (toRemove > node->data)
      node->right = removeHelper(toRemove, node->right);
    else
      return removeNode(node);
    return node;
  }

public:
  BinaryTree(N *root, std::size_t n) : root(root), n(n) {}

  bool contains(const T &toFind)
  {
    auto [found, _] = search(toFind, root);
    return found != nullptr;
  }

  bool empty()
  {
    if (!root)
      return true;
    return false;
  }

  std::size_t size()
  {
    return n;
  }

  // FIXME: To conform to the std, this should be called "erase" and return
  // the number of elements removed
  virtual std::size_t remove(const T &toRemove)
  {
    if (!root)
      return 0;
    if (toRemove == root->data)
    {
      N *oldRoot = root;
      root = removeNode(root);
      return 1;
    }
    auto *result = removeHelper(toRemove, root);
    if (result)
      return 1;
    return 0;
  }

  const T &findMin() const
  {
    return findMin(root)->data;
  }

  const T &findMax() const
  {
    return findMax(root)->data;
  }

  N *getRoot()
  {
    return root;
  }

  void clear()
  {
    clear(root);
    n = 0;
  }

  BinaryNodeIterator<T, N> begin()
  {
    return BinaryNodeIterator<T, N>(root, root);
  }

  BinaryNodeIterator<T, N> end()
  {
    return BinaryNodeIterator<T, N>(nullptr, root);
  }
};

template<typename StructureType> struct IsTreeType : public std::false_type
{
};

template<typename T, typename NodeType>
struct IsTreeType<ev::AVLTree<T, NodeType>> : public std::true_type
{
};

template<typename T>
struct IsTreeType<BinarySearchTree<T>> : public std::true_type
{
};

template<typename T>
concept IsTree = IsTreeType<T>() == true;
} // namespace ev

#endif
