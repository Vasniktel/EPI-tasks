#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  vector<int> result;

  int i = 0, j = 0, n = A.size(), m = B.size();
  while (i < n && j < m) {
    int a = A[i], b = B[j];
    if (a <= b) i++;
    if (a >= b) j++;
    if (a == b && (result.empty() || a != result.back()))
      result.push_back(a);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
