#ifndef EV_NODE_HPP
#define EV_NODE_HPP

namespace ev
{

template<typename T, typename N> struct BinaryNodeBase
{
  T data;
  N *left;
  N *right;
  N *parent;

  BinaryNodeBase(T data, N *left, N *right, N *parent = nullptr)
      : data(data), left(left), right(right), parent(parent)
  {
  }

  BinaryNodeBase(N *parent)
      : data(T()), left(nullptr), right(nullptr), parent(parent)
  {
  }

  BinaryNodeBase() : data(T()), left(nullptr), right(nullptr), parent(nullptr)
  {
  }

  virtual bool isExternal() const
  {
    if (left == nullptr && right == nullptr)
      return true;
    return false;
  }
};

// Disgusting
template<typename T> struct BinaryNode : public BinaryNodeBase<T, BinaryNode<T>>
{
  using BinaryNodeBase<T, BinaryNode<T>>::BinaryNodeBase;
};

template<typename T> struct AVLNode : public BinaryNodeBase<T, AVLNode<T>>
{
  int height;

  AVLNode(const T &data, AVLNode *left, AVLNode *right, AVLNode *parent,
          int height)
      : BinaryNodeBase<T, AVLNode>(data, left, right, parent), height(height)
  {
  }

  AVLNode()
      : BinaryNodeBase<T, AVLNode>(T(), nullptr, nullptr, nullptr), height(0)

  {
  }

  AVLNode(AVLNode *parent)
      : BinaryNodeBase<T, AVLNode>(T(), nullptr, nullptr, parent), height(0)
  {
  }

  AVLNode(const T &data, int height)
      : BinaryNodeBase<T, AVLNode>(data, nullptr, nullptr, nullptr),
        height(height)
  {
  }

  AVLNode(const T &data, AVLNode *parent, int height)
      : BinaryNodeBase<T, AVLNode>(data, nullptr, nullptr, parent),
        height(height)
  {
  }

  bool isLeaf() const
  {
    if (this->left == nullptr && this->right == nullptr)
      return true;
    return false;
  }

  bool isExternal() const override
  {
    if (height == 0)
      return true;
    return false;
  }
};

template<typename Key, typename T>
struct MapNode : public BinaryNodeBase<Key, MapNode<Key, T>>
{
  using Node = BinaryNodeBase<Key, MapNode<Key, T>>;
  T value;
  MapNode() : Node(), value(T()) {}

  MapNode(const Key &key, int height, const T &value)
      : Node(key, height), value(value)
  {
  }
};
} // namespace ev

#endif
