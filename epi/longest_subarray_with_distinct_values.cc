#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int LongestSubarrayWithDistinctEntries(const vector<int>& A) {
  std::unordered_set<int> set;

  int result = 0;
  for (int i = 0, j = 0, n = A.size(); j < n; ++i, ++j) {
    while (j < n && !set.count(A[j])) set.insert(A[j++]);
    result = std::max(result, j - i);
    if (j == n) break;
    while (A[i] != A[j]) set.erase(A[i++]);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_subarray_with_distinct_values.cc",
                         "longest_subarray_with_distinct_values.tsv",
                         &LongestSubarrayWithDistinctEntries,
                         DefaultComparator{}, param_names);
}
