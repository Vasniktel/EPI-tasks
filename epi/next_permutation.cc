#include <vector>
#include <deque>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> NextPermutation(vector<int> perm) {
  using ::std::reverse;
  using ::std::upper_bound;
  using ::std::iter_swap;

  for (int i = static_cast<int>(perm.size()) - 1; i > 0; --i) {
    if (perm[i - 1] < perm[i]) {
      reverse(perm.begin() + i, perm.end());
      iter_swap(perm.begin() + (i - 1),
          upper_bound(perm.begin() + i, perm.end(), perm[i - 1]));
      return perm;
    }
  }

  return {};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
