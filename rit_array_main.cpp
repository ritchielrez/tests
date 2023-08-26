#include <algorithm>
#include <iostream>

#define RIT_ARRAY_IMPLEMENTATION
#include "./rit_array.hpp"

int main() {
  rit::array arr{1, 2, 3, 4, 5};

  for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  arr[0] = 2;
  std::cout << arr[0] << "\n";

  return 0;
}
