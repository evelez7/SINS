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
  
  T *deallocate(T *p, size_t n) {
    delete p[n];
    return p;
  }
};
} // namespace ev

#endif
