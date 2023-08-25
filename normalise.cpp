#include <iostream>

float length(float x, float y) { return sqrt((x * x) + (y * y)); }

float normalise(float x, float y) {
  return x /= length(x, y), x /= length(x, y);
}

int main(int argc, char **argv) {
  float num1 = 12, num2 = 14;

  std::cout << normalise(num1, num2) << "\n";
}
