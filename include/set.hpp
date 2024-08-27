#ifndef EV_SET_HPP
#define EV_SET_HPP

#include "avl_tree.hpp"
#include "binary_tree_mixin.hpp"

namespace ev
{

template<typename T, typename Structure = ev::AVLTree<T>>
  requires IsTree<Structure>
class set
{
  /// the backing structure
  Structure s;

public:
  set() = default;

  typename Structure::InsertResult insert(T const &value)
  {
    return s.insert(value);
  }

  void clear()
  {
    s.clear();
  }

  bool empty()
  {
    return s.empty();
  }

  void remove(const T &value)
  {
    s.remove(value);
  }

  std::size_t size()
  {
    return s.size();
  }
};
} // namespace ev

#endif
