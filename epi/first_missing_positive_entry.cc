#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

// A is passed by value argument, since we change it.
int FindFirstMissingPositive(vector<int> A) {
  for (int i = 0, n = A.size(); i < n;) {
    if (A[i] > 0 && A[i] <= n && A[A[i] - 1] != A[i]) {
      ::std::swap(A[i], A[A[i] - 1]);
    } else {
      ++i;
    }
  }

  int result = 1;
  for (int val : A) {
    if (val == result) result++;
    if (val < result) continue;
    if (val > result) break;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "first_missing_positive_entry.cc",
                         "first_missing_positive_entry.tsv",
                         &FindFirstMissingPositive, DefaultComparator{},
                         param_names);
}
