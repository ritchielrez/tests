#ifndef RIT_ARRAY_H_INCLUDED
#define RIT_ARRAY_H_INCLUDED

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <type_traits>

namespace rit {
template <typename First, typename... Rest>
struct array_enforce_type {
  static_assert(std::conjunction_v<std::is_same<First, Rest>...>,
                "Make sure all array elements have the same type");
  using type = First;
};

template <typename T, std::size_t capacity>
struct array {
  T arr[capacity];

  // Returning a reference so if user wants to change value of index they can
  // because a reference is returned
  T &operator[](const int64_t t_index);

  // Two const qualifiers to indicate that this operator cannot be used to
  // change value of a specific index. This is meant to be used for const
  // arrays. The 1st const qualifier makes sure that the operator returns a
  // const ref to index, implying it is not possible to change the index. The
  // last const qualifier in the bottom line is used to imply that this function
  // does not change any data members of this class.
  const T &operator[](const int64_t t_index) const;

  class iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type *;
    using reference = value_type &;

    inline iterator(pointer t_ptr) : m_ptr(t_ptr) {}

    inline reference operator*() { return *m_ptr; }

    inline pointer operator->() { return m_ptr; }

    inline iterator &operator++() {
      m_ptr++;
      return *this;
    }

    // This `int` type argument is what c++ uses to differentiate between
    // postfix and prefix operators This the postfix version
    inline iterator &operator++(int) {
      iterator tmp = *this;
      m_ptr++;
      return tmp;
    }

    // NOTE: when defining functions, variables or arguments, always think where
    // they should be const-qualified or not meaning do they need to change some
    // data or not

    // NOTE: to prevent copies of objects(e.g: iterators) passed to functions
    // consider using references always
    inline friend bool operator==(const iterator &t_it1,
                                  const iterator &t_it2) {
      return t_it1.m_ptr == t_it2.m_ptr;
    }

    inline friend bool operator!=(const iterator &t_it1,
                                  const iterator &t_it2) {
      return t_it1.m_ptr != t_it2.m_ptr;
    }

   private:
    pointer m_ptr;
  };

  inline iterator begin() { return iterator(&arr[0]); }

  inline iterator end() {
    return iterator(&arr[capacity]);  // end is never reached
  }

  class const_iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type *;
    using reference = value_type &;

    inline const_iterator(pointer t_ptr) : m_ptr(t_ptr) {}

    inline const reference operator*() const { return *m_ptr; }
    inline const pointer operator->() const { return m_ptr; }

    inline const const_iterator &operator++() {
      m_ptr++;
      return *this;
    }
    inline const const_iterator &operator++(int) {
      const_iterator &tmp = *this;
      m_ptr++;
      return tmp;
    }

    inline friend bool operator==(const const_iterator &t_it1,
                                  const const_iterator &t_it2) {
      return t_it1.m_ptr == t_it2.m_ptr;
    }
    inline friend bool operator!=(const const_iterator &t_it1,
                                  const const_iterator &t_it2) {
      return t_it1.m_ptr != t_it2.m_ptr;
    }

   private:
    pointer m_ptr;
  };

  inline const_iterator cbegin() { return const_iterator(&arr[0]); }
  inline const_iterator cend() { return const_iterator(&arr[capacity]); }
};

template <typename First, typename... Rest>
array(First, Rest...)
    -> array<typename array_enforce_type<First, Rest...>::type,
             sizeof...(Rest) + 1>;
};  // namespace rit

#endif  // RIT_ARRAY_H_INCLUDED

#ifdef RIT_ARRAY_IMPLEMENTATION

namespace rit {
template <typename T, std::size_t capacity>
T &array<T, capacity>::operator[](const int64_t t_index) {
  if (t_index < 0) {
    std::cerr << "Invalid negative array index\n";
    exit(EXIT_FAILURE);
  };

  if (t_index >= capacity) {
    std::cerr << "Array index access out of bound\n";
    exit(EXIT_FAILURE);
  }

  return arr[t_index];
}

template <typename T, std::size_t capacity>
const T &array<T, capacity>::operator[](const int64_t t_index) const {
  if (t_index < 0) {
    std::cerr << "Invalid negative array index\n";
    exit(EXIT_FAILURE);
  };

  if (t_index >= capacity) {
    std::cerr << "Array index access out of bound\n";
    exit(EXIT_FAILURE);
  }

  return arr[t_index];
}

};  // namespace rit

#endif  // RIT_ARRAY_IMPLEMENTATION
