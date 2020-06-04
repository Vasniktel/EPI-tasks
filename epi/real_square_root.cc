#include "test_framework/generic_test.h"

int comp(double a, double b) {
  constexpr double eps = std::numeric_limits<double>::epsilon();
  auto val = (a - b) / b;
  if (val < -eps) return -1;
  if (val > eps) return 1;
  return 0;
}

double SquareRoot(double x) {
  double lo, hi;

  if (x < 1.0) lo = x, hi = 1.0;
  else lo = 1.0, hi = x;
  
  while (comp(lo, hi) < 0) {
    auto mi = lo + (hi - lo) * 0.5;
    
    if (comp(mi * mi, x) < 0) lo = mi;
    else if (comp(mi * mi, x) > 0) hi = mi;
    else return mi;
  }
  
  return lo;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
