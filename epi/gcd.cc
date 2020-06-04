#include "test_framework/generic_test.h"
using ::std::min;
using ::std::max;

unsigned long long recur(unsigned long long x, unsigned long long y) {
  if (x == y || y == 0) return x;
  auto a = x & 1u, b = y & 1u;
  if (a == 0 && b == 0) return recur(x >> 1u, y >> 1u) << 1u;
  if (a == 1 && b == 1) return recur(max(x - y, y), min(x - y, y));
  if (b == 0) return recur(x, y >> 1u);
  return recur(max(x >> 1u, y), min(x >> 1u, y));
}


long long Gcd(long long x, long long y) {
  return recur(max(x, y), min(x, y));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "gcd.cc", "gcd.tsv", &Gcd, DefaultComparator{},
                         param_names);
}
