#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  if (A.empty()) return -1;
  int lo = 0, hi = static_cast<int>(A.size()) - 1;

  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;

    if (A[mid] < k) lo = mid + 1;
    else hi = mid;
  }

  return A[lo] == k ? lo : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
