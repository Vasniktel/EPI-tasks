#include "test_framework/generic_test.h"
int Divide(int x, int y) {
  int result = 0;
  auto k = 32u;
  auto power = static_cast<unsigned long long>(y) << k;

  while (x >= y) {
    while (power > x) {
      power >>= 1u;
      k--;
    }

    result += 1u << k;
    x -= power;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
                         &Divide, DefaultComparator{}, param_names);
}
