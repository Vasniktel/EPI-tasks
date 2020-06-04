#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
int ComputeBinomialCoefficient(int n, int k) {
  vector<int> dp(k + 1, 1);

  for (int i = 1; i <= n; ++i) {
    int diag = 1;
    for (int j = 1; j <= k; ++j) {
      if (j >= i) break;
      int new_diag = dp[j];
      dp[j] += diag;
      diag = new_diag;
    }
  }

  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(
      args, "binomial_coefficients.cc", "binomial_coefficients.tsv",
      &ComputeBinomialCoefficient, DefaultComparator{}, param_names);
}
