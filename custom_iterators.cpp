#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>

struct Integers {
  int data[100];

  class Iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int *;
    using reference = int &;

    Iterator(pointer t_ptr) : m_ptr(t_ptr) {}

    reference operator*() const { return *m_ptr; }

    pointer operator->() { return m_ptr; }

    // Prefix incerement operator
    Iterator &operator++() {
      m_ptr++;
      return *this;
    }

    // Postfix incerement operator
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator &it1, const Iterator &it2) {
      return it1.m_ptr == it2.m_ptr;
    }

    friend bool operator!=(const Iterator &it1, const Iterator &it2) {
      return it1.m_ptr != it2.m_ptr;
    }

   private:
    pointer m_ptr;
  };

  Iterator begin() { return Iterator(&data[0]); }

  Iterator end() {
    return Iterator(&data[100]);  // Expected behaviour actually
  }
};

int main() {
  Integers ints;

  std::fill(ints.begin(), ints.end(), 0);

  for (auto it = ints.begin(); it != ints.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  return 0;
}
