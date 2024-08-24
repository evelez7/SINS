#ifndef EV_NODE_HPP
#define EV_NODE_HPP

namespace ev
{
template<typename T> class Node
{
public:
  T data;

  Node(T data) : data(data) {}
};

namespace
{
template<typename T, typename N> class BinaryTreeNode : public Node<T>
{
public:
  N *left;
  N *right;

  BinaryTreeNode(T data, N *left, N *right)
      : Node<T>(data), left(left), right(right)
  {
  }

  BinaryTreeNode() : Node<T>(T()), left(nullptr), right(nullptr) {}

  virtual bool isLeaf() const
  {
    if (!this->left && !this->right)
      return true;
    return false;
  }
};
} // namespace

// Disgusting
template<typename T> class BinaryNode : public BinaryTreeNode<T, BinaryNode<T>>
{
public:
  BinaryNode(const T &data, BinaryNode *left, BinaryNode *right)
      : BinaryTreeNode<T, BinaryNode>(data, left, right)
  {
  }

  BinaryNode() : BinaryTreeNode<T, BinaryNode>(T(), nullptr, nullptr) {}

  BinaryNode(const T &data)
      : BinaryTreeNode<T, BinaryNode>(data, new BinaryNode<T>(),
                                      new BinaryNode<T>())
  {
  }
};

template<typename T> class AVLNode : public BinaryTreeNode<T, AVLNode<T>>
{
public:
  int height;
  AVLNode<T> *parent;

  AVLNode(const T &data, AVLNode *left, AVLNode *right, AVLNode *parent,
          int height)
      : BinaryTreeNode<T, AVLNode>(data, left, right), height(height),
        parent(parent)
  {
  }

  AVLNode()
      : BinaryTreeNode<T, AVLNode>(T(), nullptr, nullptr), height(0),
        parent(nullptr)
  {
  }

  AVLNode(AVLNode *parent)
      : BinaryTreeNode<T, AVLNode>(T(), nullptr, nullptr), height(0),
        parent(parent)
  {
  }

  bool isLeaf() const override
  {
    if (height == 0 || (this->left == nullptr && this->right == nullptr))
      return true;
    return false;
  }
};
} // namespace ev

#endif
