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
  T &operator[](const int64_t t_index) {
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

  class iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type *;
    using reference = value_type &;

    iterator(pointer t_ptr) : m_ptr(t_ptr) {}

    reference operator*() { return *m_ptr; }

    pointer operator->() { return m_ptr; }

    iterator &operator++() {
      m_ptr++;
      return *this;
    }

    // This `int` type argument is what c++ uses to differentiate between
    // postfix and prefix operators This the postfix version
    iterator &operator++(int) {
      iterator tmp = *this;
      m_ptr++;
      return tmp;
    }

    // NOTE: when defining functions, variables or arguments, always think where
    // they should be const-qualified or not meaning do they need to change some data or not

    // NOTE: to prevent copies of objects(e.g: iterators) passed to functions
    // consider using references always
    friend bool operator==(const iterator &t_it1, const iterator &t_it2) {
      return t_it1.m_ptr == t_it2.m_ptr;
    }

    friend bool operator!=(const iterator &At_it1, const iterator &t_it2) {
      return t_it1.m_ptr != t_it2.m_ptr;
    }

   private:
    pointer m_ptr;
  };

  class const_iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type *;
    using reference = value_type &;
  };

  iterator begin() { return iterator(&arr[0]); }

  iterator end() {
    return iterator(&arr[capacity]);  // end is never reached
  }
};

template <typename First, typename... Rest>
array(First, Rest...)
    -> array<typename array_enforce_type<First, Rest...>::type,
             sizeof...(Rest) + 1>;
};  // namespace rit

int main() {
  rit::array arr{1, 2, 3, 4, 5};

  for (const int &e : arr) {
    std::cout << e << " ";
  }
  std::cout << "\n";

  arr[0] = 2;
  std::cout << arr[0] << "\n";
}
