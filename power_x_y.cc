#include "test_framework/generic_test.h"

double Power(double x, int y) {
  auto result = 1.0;
  int sign = y < 0 ? -1 : 1;
  y = abs(y);

  while (y > 0) {
    if (y & 1u) result *= x;
    x *= x;
    y /= 2;
  }

  if (sign < 0) return 1.0 / result;
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
