#include <iostream>

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  std::size_t size_arr = sizeof(arr);
  std::size_t size_arr_plus_1 = sizeof(arr) + 1;
  int *ptr = arr;

  std::cout << "Size of the arr: " << size_arr << "\n";
  std::cout << "sizeof(arr) + 1: " << size_arr_plus_1 << "\n";
  std::cout << ptr << "\n";
  std::cout << ptr + 1 << "\n";
}
