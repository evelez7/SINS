#ifndef EV_AVL_TREE_H
#define EV_AVL_TREE_H

#include "binary_tree_mixin.hpp"
#include "node.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>
#include <utility>

namespace ev
{
/// AVL Tree
/// Implemented according to Goodrich, Tamassia
///
/// Implementation assumes leafs are actually nodes with 0 height and nullptr
/// children
///
/// FIXME: Consider an implementation where leafs are actually nullptr
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
    if (!node || (!node->left && !node->right))
    {
      heights[0] = 0;
      heights[1] = 0;
    }
    else if (!node->left && node->right)
    {
      heights[0] = 0;
      heights[1] = node->right->height;
    }
    else if (node->left && !node->right)
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

  AVLNode<T> *getShortestChild(AVLNode<T> *node)
  {
    if (!node->left)
      return node->right;
    if (!node->right)
      return node->left;
    return node->left->height < node->right->height ? node->left : node->right;
  }

  void rebalance(AVLNode<T> *node)
  {
    auto heights = getHeights(node);
    node->height = 1 + std::max(heights[0], heights[1]);
    while (node != nullptr)
    {
      auto childrenHeights = getHeights(node);
      if (abs(childrenHeights[0] - childrenHeights[1]) > 1)
      {
        AVLNode<T> *tallestChild;
        if (childrenHeights[0] > childrenHeights[1])
          tallestChild = node->left;
        else
          tallestChild = node->right;

        AVLNode<T> *tallestGrandchild;
        auto grandchildHeights = getHeights(tallestChild);
        if (grandchildHeights[0] > grandchildHeights[1])
          tallestGrandchild = tallestChild->left;
        else
          tallestGrandchild = tallestChild->right;
        node = restructure(tallestGrandchild);
      }

      childrenHeights = getHeights(node);
      node->height = 1 + std::max(childrenHeights[0], childrenHeights[1]);
      node = node->parent;
    }
  }

  bool checkBalance(AVLNode<T> *node)
  {
    if (!node || node->isLeaf())
      return true;

    int leftHeight = !node->left ? 0 : node->left->height;
    int rightHeight = !node->right ? 0 : node->right->height;

    if (std::abs(leftHeight - rightHeight) > 1)
      return false;

    int expectedHeight = 1 + std::max(leftHeight, rightHeight);
    if (node->height != expectedHeight)
      return false;

    return checkBalance(node->left) && checkBalance(node->right);
  }

public:
  AVLTree() : BinaryTree<T, AVLNode<T>>(nullptr, 0) {}
  ~AVLTree()
  {
    BinaryTree<T, AVLNode<T>>::clear();
  }

  typedef std::pair<BinaryNodeIterator<T, AVLNode<T>>, bool> InsertResult;
  InsertResult insert(const T &toInsert)
  {
    if (!this->root)
    {
      this->root = new AVLNode<T>(toInsert, 1);
      ++this->n;
      return InsertResult(
          BinaryNodeIterator<T, AVLNode<T>>(this->root, this->root), true);
    }

    auto [found, parent] = this->search(toInsert, this->root);
    if (found)
      return InsertResult(BinaryNodeIterator<T, AVLNode<T>>(found, this->root),
                          false);

    AVLNode<T> *newNode = new AVLNode<T>(toInsert, 1);
    newNode->parent = parent;
    if (toInsert < parent->data)
      parent->left = newNode;
    else
      parent->right = newNode;
    ++this->n;

    rebalance(newNode);

    return InsertResult(BinaryNodeIterator<T, AVLNode<T>>(newNode, this->root),
                        true);
  }

  bool checkBalance()
  {
    return checkBalance(this->root);
  }

  /// Goodrich, Tamassia page 125
  std::size_t remove(const T &toRemove) override
  {
    auto [found, parent] = this->search(toRemove, this->root);
    if (!found)
      return 0;

    auto *nodeToRebalance = found->parent;

    if (found->left && found->right)
    {
      auto *nextMin = this->findMax(found->left);
      found->data = nextMin->data;
      found = nextMin;
      nodeToRebalance = found->parent;
    }

    auto *child = found->left ? found->left : found->right;
    if (found->parent)
    {
      if (found->parent->left == found)
        found->parent->left = child;
      else
        found->parent->right = child;
    }
    else
    {
      this->root = child;
    }

    if (child)
      child->parent = found->parent;

    delete found;
    --this->n;
    rebalance(nodeToRebalance);
    return 1;
  }
};
} // namespace ev

#endif