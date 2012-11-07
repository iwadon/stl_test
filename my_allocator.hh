#ifndef MY_ALLOCATOR_HPP_INCLUDED
#define MY_ALLOCATOR_HPP_INCLUDED 1

#include <cstddef>

template <class T>
class MyAllocator;

template <>
class MyAllocator<void>
{
public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef void *pointer;
  typedef const void *const_pointer;
  typedef void value_type;

  template <class T1>
  struct rebind
  {
    typedef MyAllocator<T1> other;
  };
};

template <class T>
class MyAllocator
{
public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T value_type;

  template <class T1>
  struct rebind
  {
    typedef MyAllocator<T1> other;
  };

  MyAllocator() throw() {}

  MyAllocator(const MyAllocator &) throw() {}

  template <class T1>
  MyAllocator(const MyAllocator<T1> &) throw() {}

  ~MyAllocator() throw() {}

  pointer address(reference x) const
  {
    return &x;
  }

  const_pointer address(const_reference x) const
  {
    return &x;
  }

  pointer allocate(size_type n, MyAllocator<void>::const_pointer /*hint*/ = 0)
  {
    return static_cast<T *>(malloc(n * sizeof (T)));
  }

  void deallocate(pointer p, size_type)
  {
    free(p);
  }

  size_type max_size() const
  {
    return size_type(-1) / sizeof (T);
  }

  void construct(pointer p, const T &value)
  {
    new(p) T(value);
  }

  void destroy(pointer p)
  {
    p->~T();
  }
};

template <class T1, class T2>
bool operator==(const MyAllocator<T1> &, const MyAllocator<T2> &) throw()
{
  return true;
}

template <class T1, class T2>
bool operator!=(const MyAllocator<T1> &, const MyAllocator<T2> &) throw()
{
  return false;
}

#endif // !defined(MY_ALLOCATOR_HPP_INCLUDED)
