#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A) {
  if (A.empty()) return -1;
  int lo = 0, hi = A.size() - 1;

  while (lo < hi) {
    int mi = lo + (hi - lo) / 2;

    if (A[lo] < A[hi]) return lo;
    if (A[mi] < A[hi]) hi = mi;
    else lo = mi + 1;
  }

  return lo;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
