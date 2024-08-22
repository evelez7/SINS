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

  BinaryTreeNode(N *left, N *right, T data)
      : Node<T>(data), left(left), right(right)
  {
  }
};
} // namespace

// Disgusting
template<typename T> class BinaryNode : public BinaryTreeNode<T, BinaryNode<T>>
{
public:
  BinaryNode(const T &data, BinaryNode *left, BinaryNode *right)
      : BinaryTreeNode<T, BinaryNode>(left, right, data)
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
      : BinaryTreeNode<T, AVLNode>(left, right, data), height(height),
        parent(parent)
  {
  }
};
} // namespace ev

#endif
