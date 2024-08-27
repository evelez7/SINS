#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "binary_tree_mixin.hpp"
#include "node.hpp"
#include <utility>
namespace ev
{
/**
  Implemented according to Weiss, 4th ed.
*/
template<typename T>
class BinarySearchTree : public BinaryTree<T, BinaryNode<T>>
{

  BinaryNode<T> *insert(const T &toInsert, BinaryNode<T> *&node,
                        BinaryNode<T> *parent = nullptr)
  {
    if (!node)
    {
      node = new BinaryNode<T>(toInsert, nullptr, nullptr, parent);
      ++this->n;
      return node;
    }
    else if (toInsert < node->data)
      return insert(toInsert, node->left, node);
    else if (toInsert > node->data)
      return insert(toInsert, node->right, node);
    return nullptr;
  }

public:
  BinarySearchTree() : BinaryTree<T, BinaryNode<T>>(nullptr, 0) {}

  ~BinarySearchTree()
  {
    BinaryTree<T, BinaryNode<T>>::clear(this->root);
  }

  std::pair<BinaryNode<T> *, bool> insert(const T &toInsert)
  {
    if (!this->root)
    {
      this->root = new BinaryNode<T>(toInsert, nullptr, nullptr, nullptr);
      ++this->n;
      return std::make_pair(this->root, true);
    }

    auto result = insert(toInsert, this->root);
    if (result)
    {
      return std::make_pair(result, true);
    }
    return std::make_pair(nullptr, false);
  }
};
} // namespace ev

#endif
