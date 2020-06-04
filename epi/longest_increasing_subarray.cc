#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

struct Subarray {
  int start = 0, end = 0;
};

Subarray FindLongestIncreasingSubarray(const vector<int>& A) {
  int max_start = 0, max_end = 0;

  for (int i = 0, n = A.size(); i < n;) {
    int start = i, end = i;
    for (++i; i < n && A[i] > A[i - 1]; ++i) {
      end++;
    }

    if (end - start > max_end - max_start) {
      max_end = end, max_start = start;
    }
  }

  return {max_start, max_end};
}
int FindLongestIncreasingSubarrayWrapper(const vector<int>& A) {
  Subarray result = FindLongestIncreasingSubarray(A);
  return result.end - result.start + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_increasing_subarray.cc", "longest_increasing_subarray.tsv",
      &FindLongestIncreasingSubarrayWrapper, DefaultComparator{}, param_names);
}
