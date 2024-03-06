#ifndef EV_VECTOR_HPP
#define EV_VECTOR_HPP

#include "allocator.hpp"
#include <cstddef>
#include <stdexcept>

namespace ev {
template <typename T, typename Allocator = ev::Allocator<T>> class vector {
  size_t count;
  size_t possibleCount;
  Allocator allocator;
  T *p;

public:
  vector() : count(0), possibleCount(0) {}

  vector(size_t count) : count(count), possibleCount(count) {
    p = allocator.allocate(count);
  }

  size_t size() { return count; }

  size_t capacity() { return possibleCount; }

  void push_back(const T &value) {
    if (count == 0) {
      p = allocator.allocate(1);
      p[0] = value;
      possibleCount += 1;
    } else if (count + 1 > possibleCount) {
      T *temp = allocator.allocate(count + 1);
      for (size_t i = 0; i < count; ++i)
        temp[i] = p[i];
      p = temp;
      p[count] = value;
      possibleCount = count + 1;
    } else
      p[count + 1] = value;

    count += 1;
  }

  void pop_back() {
    // p = allocator.deallocate(p, count);
    count -= 1;
  }

  void reserve(size_t new_cap) {
    // FIXME: check if new cap > max_size(), implement max_size()
    if (new_cap <= possibleCount)
      return;
    if (count == 0) {
      p = allocator.allocate(new_cap);
      possibleCount = new_cap;
      return;
    }
    T *temp = allocator.allocate(new_cap);
    for (size_t i = 0; i < count; ++i)
      temp[i] = p[i];
    p = temp;
    possibleCount = new_cap;
  }

  bool empty() {
    if (count == 0)
      return true;
    return false;
  }

  T &operator[](size_t pos) { return p[pos]; }

  T &at(size_t pos) {
    if (pos > size())
      throw std::out_of_range(
          "Position is greater than the size of the vector");
    return p[pos];
  }

  T *data() { return p; }
  
  T &front() {
    return p[0];
  }
  
  T &back() {
    return p[count - 1];
  }
};
} // namespace ev

#endif
