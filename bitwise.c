#include <stdio.h>

int main() {
  int integer = 12;   // 1100
  int integer2 = 10;  // 1010

  printf("Bitwise shifting(<<) %d by 2, result = %d\n", integer, integer << 2);
  printf("Bitwise shifting(>>) %d by 2, result = %d\n", integer, integer >> 2);

  printf("Bitwise OR between %d and %d, result = %d\n", integer, integer2,
         integer | integer2);  // 1110
  printf("Bitwise XOR between %d and %d, result = %d\n", integer, integer2,
         integer ^ integer2);  // 0110
  printf("Bitwise AND between %d and %d, result = %d\n", integer, integer2,
         integer & integer2);  // 1000

  // The `~integer` evaluates to this 1111111111110011
  // Because `~` operator flips 0's to 1's and 1's to 0's.
  // 12 is equals to 1100, but it is stored as 0000000000001100,
  // because a signed int value is stored as a 16 bit binary.
  printf("Bitwise NOT of %d, result = %d\n", integer, ~integer);

  return 0;
}
