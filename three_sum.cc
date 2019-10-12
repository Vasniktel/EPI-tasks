#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

bool HasThreeSum(vector<int> A, int t) {
  std::sort(A.begin(), A.end());

  for (int i = 0, n = A.size(); i < n; ++i) {
    int lo = i, hi = n - 1;
    while (lo <= hi) {
      int val = A[i] + A[lo] + A[hi];
      if (val < t) lo++;
      else if (val > t) hi--;
      else return true;
    }
  }

  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
