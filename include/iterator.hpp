#ifndef EV_ITERATOR_HPP
#define EV_ITERATOR_HPP

namespace ev
{
template<typename T> class iterator
{
protected:
  T *current;

public:
  iterator(T *ptr) : current(ptr) {}

  T *operator->()
  {
    return current;
  }

  virtual T &operator*()
  {
    return *current;
  }
};

} // namespace ev

#endif
