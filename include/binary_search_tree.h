#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "binary_tree_mixin.hpp"
#include "node.hpp"

namespace ev
{
/**
  Implemented according to Weiss, 4th ed.
*/
template<typename T>
class BinarySearchTree : public BinaryTree<T, BinaryNode<T>>
{

  bool insert(const T &toInsert, BinaryNode<T> *&node)
  {
    if (!node || node->isLeaf())
    {
      node = new BinaryNode<T>(toInsert);
      ++this->n;
      return true;
    }
    else if (toInsert < node->data)
      return insert(toInsert, node->left);
    else if (toInsert > node->data)
      return insert(toInsert, node->right);
    return false;
  }

public:
  BinarySearchTree() : BinaryTree<T, BinaryNode<T>>(nullptr, 0) {}

  ~BinarySearchTree()
  {
    BinaryTree<T, BinaryNode<T>>::clear(this->root);
  }

  bool insert(const T &toInsert)
  {
    return insert(toInsert, this->root);
  }
};
} // namespace ev

#endif
