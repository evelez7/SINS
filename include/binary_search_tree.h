#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

/**
  Implemented according to Weiss, 4th ed.
*/
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
    if (!node)
      return nullptr;
    if (node->right == nullptr)
      return node;
    return findMax(node->right);
  }

  void remove(const T &toRemove, Node *&node)
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
      Node *old = node;
      node = (node->left != nullptr) ? node->left : node->right;
      delete old;
      old = nullptr;
    }
  }

  void clear(Node *node)
  {
    if (!node)
      return;
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
  }

public:
  BinarySearchTree() : root(nullptr) {}

  ~BinarySearchTree()
  {
    clear(root);
  }

  virtual bool insert(const T &toInsert)
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

  void remove(const T &toRemove)
  {
    remove(toRemove, root);
  }

  void clear()
  {
    clear(root);
  }
};

#endif
