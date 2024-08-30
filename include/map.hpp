#ifndef EV_MAP_HPP
#define EV_MAP_HPP

#include "avl_tree.hpp"
#include "binary_node_iterator.hpp"
#include "node.hpp"
#include <utility>

namespace ev
{
template<typename Key, typename T,
         typename Structure = AVLTree<T, MapNode<Key, T>>>
class map
{
  using Node = MapNode<Key, T>;
  Node *root;
  Structure tree;

public:
  using iterator = BinaryNodeIterator<T, MapNode<Key, T>>;
  using InsertResult = std::pair<iterator, bool>;

  map() = default;

  InsertResult insert(const Key &key, const T &data)
  {
    return tree.insert(data);
  }

  iterator find(const Key &key)
  {
    return tree.find(key);
  }

  iterator remove(const Key &key)
  {
    return tree.remove(key);
  }

  std::size_t size()
  {
    return tree.size();
  }

  T &at(const Key &key)
  {
    auto [found, _] = tree.search(key, root);
    if (!found)
      throw std::out_of_range("Key not found");
    return found->data;
  }
};
} // namespace ev

#endif
