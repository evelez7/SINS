#ifndef EV_BINARY_NODE_ITERATOR_HPP
#define EV_BINARY_NODE_ITERATOR_HPP

#include "iterator.hpp"
#include "node.hpp"

namespace ev
{
template<typename T, typename N>
class BinaryNodeIterator : public iterator<BinaryNodeBase<T, N>>
{
protected:
  BinaryNodeBase<T, N> *tree_root;

public:
  BinaryNodeIterator(BinaryNodeBase<T, N> *ptr, BinaryNodeBase<T, N> *root)
      : iterator<BinaryNodeBase<T, N>>(ptr), tree_root(root)
  {
  }

  // T &operator*() override
  //{
  //   return this->current;
  // }

  BinaryNodeIterator<T, N> &operator++()
  {
    if (this->current->right)
    {
      this->current = this->current->right;
      while (this->current->left)
        this->current = this->current->left;
    }
    else
    {
      BinaryNodeBase<T, N> *parent = this->current->parent;
      while (parent && this->current == parent->right)
      {
        this->current = parent;
        parent = parent->parent;
      }
      this->current = parent;
    }
    return *this;
  }

  BinaryNodeIterator<T, N> &operator--()
  {
    if (this->current == nullptr)
    {
      if (tree_root != nullptr)
      {
        this->current = tree_root;
        while (this->current->right)
          this->current = this->current->right;
      }
    }
    else if (this->current->left)
    {
      this->current = this->current->left;
      while (this->current->right)
        this->current = this->current->right;
    }
    else
    {
      BinaryNodeBase<T, N> *parent = this->current->parent;
      while (parent && this->current == parent->left)
      {
        this->current = parent;
        parent = parent->parent;
      }
      this->current = parent;
    }
    return *this;
  }
};
} // namespace ev
#endif
