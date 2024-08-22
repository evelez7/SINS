#ifndef EV_TREE_MIXIN_HPP
#define EV_TREE_MIXIN_HPP

#include <cstddef>
#include <type_traits>

namespace ev
{
template<typename T> class AVLTree;
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

  void remove(const T &toRemove, N *&node)
  {
    if (!node)
      return;
    if (toRemove < node->data)
      remove(toRemove, node->left);
    else if (toRemove > node->data)
      remove(toRemove, node->right);
    else if (node->left && node->right)
    {
      node->data = findMin(node->right)->data;
      remove(node->data, node->right);
    }
    else
    {
      N *old = node;
      node = (node->left != nullptr) ? node->left : node->right;
      delete old;
      old = nullptr;
      --n;
    }
  }

  N *findMin(N *node) const
  {
    if (node == nullptr)
      return nullptr;
    if (node->left == nullptr)
      return node;
    return findMin(node->left);
  }

  N *findMax(N *node) const
  {
    if (!node)
      return nullptr;
    if (node->right == nullptr)
      return node;
    return findMax(node->right);
  }

public:
  BinaryTree(N *root, std::size_t n) : root(root), n(n) {}

  bool contains(const T &toFind, N *&node)
  {
    if (!node)
      return false;
    else if (toFind < node->data)
      return contains(toFind, node->left);
    else if (toFind > node->data)
      return contains(toFind, node->right);
    return true;
  }

  bool contains(const T &toFind)
  {
    return contains(toFind, root);
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

  void remove(const T &toRemove)
  {
    remove(toRemove, root);
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
};

template<typename StructureType> struct IsTreeType : public std::false_type
{
};

template<typename T> struct IsTreeType<ev::AVLTree<T>> : public std::true_type
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
