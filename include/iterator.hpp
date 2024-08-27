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
};

} // namespace ev

#endif
