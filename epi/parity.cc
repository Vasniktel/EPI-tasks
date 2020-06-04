#include "test_framework/generic_test.h"
short Parity(unsigned long long x) {
  auto size = sizeof(x) * 8;

  while (true) {
    size >>= 1u;
    if (!size) break;
    x ^= x >> size;
  }

  return x & 1u;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
