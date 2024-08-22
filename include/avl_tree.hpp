#ifndef EV_AVL_TREE_H
#define EV_AVL_TREE_H

#include "binary_tree_mixin.hpp"
#include "node.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>

namespace ev
{
template<typename T> class AVLTree : public BinaryTree<T, AVLNode<T>>
{
  void updateHeights(AVLNode<T> *node)
  {
    if (node == nullptr)
      return;
    if (node->left)
      updateHeights(node->left);
    if (node->right)
      updateHeights(node->right);
    auto heights = getHeights(node);
    node->height = std::max(heights[0], heights[1]) + 1;
  }

  /**
    Trinode restructuring according to Goodrich, Tamassia
    Covers all 4 cases for rotations, the last two being double rotations
  */
  AVLNode<T> *restructure(AVLNode<T> *&node)
  {
    AVLNode<T> *a, *b, *c, *t0, *t1, *t2, *t3;
    /// let a, b, c be inorder of x, y, z where x = node, y=parent, and
    /// z=grandparent
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
    else if (node->data > node->parent->data &&
             node->parent->data < node->parent->parent->data)
    {
      b = node;
      a = b->parent;
      c = a->parent;
      t1 = b->left;
      t2 = b->right;
      t0 = a->left;
      t3 = c->right;
    }
    else
      throw std::runtime_error("restructure: node is not a child of its "
                               "parent");

    // replace the subtree rooted at z
    auto *restOfTree = node->parent->parent->parent;
    if (!restOfTree)
      this->root = b;
    else if (restOfTree->left &&
             restOfTree->left->data == node->parent->parent->data)
      restOfTree->left = b;
    else if (restOfTree->right &&
             restOfTree->right->data == node->parent->parent->data)
      restOfTree->right = b;
    else
      throw std::runtime_error("restructure: node is not a child of its "
                               "parent");
    b->parent = restOfTree;

    b->left = a;
    a->parent = b;

    a->left = t0;
    a->right = t1;
    if (t0)
      t0->parent = a;
    if (t1)
      t1->parent = a;

    b->right = c;
    c->parent = b;

    c->left = t2;
    c->right = t3;
    if (t2)
      t2->parent = c;
    if (t3)
      t3->parent = c;

    updateHeights(a);
    updateHeights(b);
    updateHeights(c);

    return b;
  }

  std::array<int, 2> getHeights(AVLNode<T> *node)
  {
    std::array<int, 2> heights;
    if (!node->left && !node->right)
    {
      heights[0] = 0;
      heights[1] = 0;
    }
    else if (!node->left)
    {
      heights[0] = 0;
      heights[1] = node->right->height;
    }
    else if (!node->right)
    {
      heights[0] = node->left->height;
      heights[1] = 0;
    }
    else
    {
      heights[0] = node->left->height;
      heights[1] = node->right->height;
    }
    return heights;
  }

  void rebalance(AVLNode<T> *node)
  {
    AVLNode<T> *tempNode = node;
    auto heights = getHeights(tempNode);
    tempNode->height = 1 + std::max(heights[0], heights[1]);
    while (tempNode != this->root)
    {
      tempNode = tempNode->parent;
      auto childrenHeights = getHeights(tempNode);
      if (abs(childrenHeights[0] - childrenHeights[1]) > 1)
      {
        AVLNode<T> *tallestChild;
        if (childrenHeights[0] > childrenHeights[1])
          tallestChild = tempNode->left;
        else
          tallestChild = tempNode->right;

        AVLNode<T> *tallestGrandchild;
        auto grandchildHeights = getHeights(tallestChild);
        if (grandchildHeights[0] > grandchildHeights[1])
          tallestGrandchild = tallestChild->left;
        else
          tallestGrandchild = tallestChild->right;
        tempNode = restructure(tallestGrandchild);
      }

      childrenHeights = getHeights(tempNode);
      tempNode->height = 1 + std::max(childrenHeights[0], childrenHeights[1]);
    }
  }

  AVLNode<T> *insert(const T &toInsert, AVLNode<T> *&node, AVLNode<T> *&parent)
  {
    if (!node)
    {
      node = new AVLNode<T>(toInsert, nullptr, nullptr, parent, 1);
      return node;
    }
    else if (toInsert < node->data)
      return insert(toInsert, node->left, node);
    else if (toInsert > node->data)
      return insert(toInsert, node->right, node);
    return nullptr;
  }

public:
  AVLTree() : BinaryTree<T, AVLNode<T>>(nullptr, 0) {}
  ~AVLTree()
  {
    BinaryTree<T, AVLNode<T>>::clear();
  }

  bool insert(const T &toInsert)
  {
    if (!this->root)
    {
      this->root = new AVLNode<T>(toInsert, nullptr, nullptr, nullptr, 1);
      ++this->n;
      return true;
    }
    AVLNode<T> *node = insert(toInsert, this->root, node->parent);
    if (node)
    {
      rebalance(node);
      ++this->n;
      return true;
    }
    return false;
  }
};
} // namespace ev

#endif
