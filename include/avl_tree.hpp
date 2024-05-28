#ifndef EV_AVL_TREE_H
#define EV_AVL_TREE_H

#include "binary_search_tree.h"
#include <algorithm>

namespace ev
{
template <typename T> class AVLTree : BinarySearchTree<T>
{
  struct AVLNode
  {
    int height;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;
    T data;
    AVLNode(const T &data, AVLNode *left, AVLNode *right, AVLNode *parent,
            int height)
        : height(height), parent(parent), left(left), right(right), data(data)
    {
    }
  };
  AVLNode *root;

  /**
    Trinode restructuring according to Goodrich, Tamassia p118
  */
  AVLNode *restructure(AVLNode *&node)
  {
    AVLNode *a, *b, *c, *t0, *t1, *t2, *t3;
    if (node->data < node->parent->data &&
        node->parent->data < node->parent->parent->data)
    {
      a = node;
      b = a->parent;
      c = b->parent;
      t0 = a->left;
      t1 = a->right;
      t2 = b->right;
      t3 = c->right;
    }
    else if (node->data > node->parent->data &&
             node->parent->data > node->parent->parent->data)
    {
      c = node;
      b = c->parent;
      a = b->parent;
      t2 = c->left;
      t3 = c->right;
      t1 = b->left;
      t0 = a->left;
    }
    else if (node->data < node->parent->data &&
             node->parent->data > node->parent->parent->data)
    {
      b = node;
      c = b->parent;
      a = c->parent;
      t1 = b->left;
      t2 = b->right;
      t3 = c->right;
      t0 = a->left;
    }
    else
    {
      b = node;
      a = b->parent;
      c = a->parent;
      t1 = b->left;
      t2 = b->right;
      t0 = a->left;
      t3 = c->right;
    }
    b->left = a;
    a->parent = b;

    a->left = t0;
    a->right = t1;
    if (t0 && t1)
    {
      t0->parent = a;
      t1->parent = a;
    }

    b->right = c;
    c->parent = b;

    c->left = t2;
    c->right = t3;
    if (t2 && t3)
    {
      t2->parent = c;
      t3->parent = c;
    }
    return b;
  }

  void rebalance(AVLNode *&node)
  {
    if (!node->left && !node->right)
      node->height = 1;
    else if (!node->left)
      node->height = 1 + node->right->height;
    else if (!node->right)
      node->height = 1 + node->left->height;
    else
      node->height = 1 + std::max(node->left->height, node->right->height);
    while (node != root)
    {
      node = node->parent;
      int leftHeight, rightHeight;
      if (!node->left)
      {
        rightHeight = node->right->height;
        leftHeight = 0;
      }
      else if (!node->right)
      {
        leftHeight = node->left->height;
        rightHeight = 0;
      }
      else
      {
        leftHeight = node->left->height;
        rightHeight = node->right->height;
      }
      if (leftHeight - rightHeight > 1)
      {
        AVLNode *tallestChild;
        if (node->left->height > node->right->height)
          tallestChild = node->left;
        else
          tallestChild = node->right;

        AVLNode *tallestGrandchild;
        if (tallestChild->left->height > tallestChild->right->height)
          tallestGrandchild = tallestChild->left;
        else
          tallestGrandchild = tallestChild->right;
        node = restructure(tallestGrandchild);
      }
      if (!node->left)
      {
        rightHeight = node->right->height;
        leftHeight = 0;
      }
      else if (!node->right)
      {
        leftHeight = node->left->height;
        rightHeight = 0;
      }
      else
      {
        leftHeight = node->left->height;
        rightHeight = node->right->height;
      }
      node->height = 1 + std::max(leftHeight, rightHeight);
    }

    auto *toFindRoot = node->parent;
    while (node->parent)
      node = node->parent;
    root = toFindRoot;
  }

  AVLNode *insert(const T &toInsert, AVLNode *&node, AVLNode *&parent)
  {
    if (!node)
    {
      int height;
      if (!parent)
        height = 0;
      else
        height = parent->height + 1;
      node = new AVLNode(toInsert, nullptr, nullptr, parent, height);
      return node;
    }
    else if (toInsert < node->data)
      return insert(toInsert, node->left, node);
    else if (toInsert > node->data)
      return insert(toInsert, node->right, node);
    return nullptr;
  }

public:
  AVLTree() : root(nullptr) {}

  virtual bool insert(const T &toInsert)
  {
    AVLNode *node;
    if (!root)
    {
      root = new AVLNode(toInsert, nullptr, nullptr, nullptr, 0);
      return true;
    }
    else
      node = insert(toInsert, root, node->parent);
    if (node && node->parent && node->parent->parent)
    {
      rebalance(node);
      return true;
    }
    else if (node)
      return true;
    return false;
  }

  AVLNode *getRoot()
  {
    return root;
  }
};
} // namespace ev

#endif
