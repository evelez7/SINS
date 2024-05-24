#ifndef EV_ALLOCATOR_HPP
#define EV_ALLOCATOR_HPP

#include <cstddef>

namespace ev {
template <typename T> class Allocator {
public:
  Allocator() = default;

  T *allocate(std::size_t n) {
    return new T[n];
  }

  void deallocate(T *p, size_t n) { delete p; }
};
} // namespace ev

#endif
