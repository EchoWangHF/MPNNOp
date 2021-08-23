#include "core/half.h"

int main() {
  half half_a = -0.3;
  std::cout << half_a << std::endl;
  half half_b = half_a;
  std::cout << half_b << std::endl;
  int32_t k = 55;
  half half_c = k;
  std::cout << half_c << std::endl;
  half_a = k;
  std::cout << half_a << std::endl;
  half_c = half_b;
  std::cout << half_c << std::endl;

  return 0;
}
