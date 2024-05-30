#ifndef EV_AVL_TREE_H
#define EV_AVL_TREE_H

#include <algorithm>
#include <array>
#include <stdexcept>

namespace ev
{
template <typename T> class AVLTree
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
    Trinode restructuring according to Goodrich, Tamassia
    Covers all 4 cases for rotations, the last two being double rotations
  */
  AVLNode *restructure(AVLNode *&node)
  {
    AVLNode *a, *b, *c, *t0, *t1, *t2, *t3;
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
    // replace the subtree rooted at z
    auto *restOfTree = node->parent->parent->parent;
    b->parent = restOfTree;
    if (restOfTree == nullptr)
      root = b;
    else if (restOfTree->left && restOfTree->left->data == b->data)
      restOfTree->left = b;
    else if (restOfTree->right && restOfTree->right->data == b->data)
      restOfTree->right = b;

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

    if (!a->left && !a->right)
      a->height = 1;
    else if (!a->left)
      a->height = a->right->height + 1;
    else if (!a->right)
      a->height = a->left->height + 1;
    else
      a->height = std::max(a->left->height, a->right->height) + 1;

    if (!b->left && !b->right)
      b->height = 1;
    else if (!b->left)
      b->height = b->right->height + 1;
    else if (!b->right)
      b->height = b->left->height + 1;
    else
      b->height = std::max(b->left->height, b->right->height) + 1;

    if (!c->left && !c->right)
      c->height = 1;
    else if (!c->left)
      c->height = c->right->height + 1;
    else if (!c->right)
      c->height = c->left->height + 1;
    else
      c->height = std::max(c->left->height, c->right->height) + 1;

    return b;
  }

  std::array<int, 2> getHeights(AVLNode *node)
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

  void rebalance(AVLNode *node)
  {
    AVLNode *tempNode = node;
    auto heights = getHeights(tempNode);
    tempNode->height = 1 + std::max(heights[0], heights[1]);
    while (tempNode != root)
    {
      tempNode = tempNode->parent;
      auto childrenHeights = getHeights(tempNode);
      if (abs(childrenHeights[0] - childrenHeights[1]) > 1)
      {
        AVLNode *tallestChild;
        if (childrenHeights[0] > childrenHeights[1])
          tallestChild = tempNode->left;
        else
          tallestChild = tempNode->right;

        AVLNode *tallestGrandchild;
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

  bool contains(const T &toFind, AVLNode *&node)
  {
    if (!node)
      return false;
    else if (toFind < node->data)
      return contains(toFind, node->left);
    else if (toFind > node->data)
      return contains(toFind, node->right);
    return true;
  }

  AVLNode *findMin(AVLNode *node) const
  {
    if (node == nullptr)
      return nullptr;
    if (node->left == nullptr)
      return node;
    return findMin(node->left);
  }

  AVLNode *findMax(AVLNode *node) const
  {
    if (!node)
      return nullptr;
    if (node->right == nullptr)
      return node;
    return findMax(node->right);
  }

  void remove(const T &toRemove, AVLNode *&node)
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
      AVLNode *old = node;
      node = (node->left != nullptr) ? node->left : node->right;
      delete old;
      old = nullptr;
    }
  }

  void clear(AVLNode *&node)
  {
    if (!node)
      return;
    if (node->left)
      clear(node->left);
    if (node->right)
      clear(node->right);
    delete node;
    node = nullptr;
  }

  AVLNode *insert(const T &toInsert, AVLNode *&node, AVLNode *&parent)
  {
    if (!node)
    {
      node = new AVLNode(toInsert, nullptr, nullptr, parent, 1);
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
  ~AVLTree()
  {
    clear(root);
  }

  bool insert(const T &toInsert)
  {
    if (!root)
    {
      root = new AVLNode(toInsert, nullptr, nullptr, nullptr, 1);
      return true;
    }
    AVLNode *node = insert(toInsert, root, node->parent);
    if (node)
    {
      rebalance(node);
      return true;
    }
    return false;
  }

  AVLNode *getRoot()
  {
    return root;
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

  bool empty()
  {
    if (!root)
      return true;
    return false;
  }
};
} // namespace ev

#endif
