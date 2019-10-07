#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  long long lo = 0, hi = k;

  while (lo <= hi) {
    auto mi = lo + (hi - lo) / 2LL;

    if (mi * mi < k) lo = mi + 1;
    else if (mi * mi > k) hi = mi - 1;
    else return mi;
  }

  return hi;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
