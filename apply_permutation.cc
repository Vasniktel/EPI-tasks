#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
void ApplyPermutation(vector<int>* perm_ptr, vector<int>* A_ptr) {
  auto& perm = *perm_ptr;
  auto& arr = *A_ptr;

  for (int i = 0, n = perm.size(); i < n; ++i) {
    if (perm[i] <= 0) continue;
    for (int j = perm[i]; j != i; j = -perm[j]) {
      ::std::swap(arr[i], arr[j]);
      perm[j] *= -1;
    }
  }
}
vector<int> ApplyPermutationWrapper(vector<int> perm, vector<int> A) {
  ApplyPermutation(&perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
