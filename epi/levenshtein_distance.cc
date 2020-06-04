#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistance(const string& A, const string& B) {
  vector<int> dp(A.size());
  for (int i = 0; i < A.size(); ++i) dp[i] = i + 1;

  for (int j = 0; j < B.size(); ++j) {
    int diag = j, left = j + 1;
    for (int i = 0, n = A.size(); i < n; ++i) {
      int new_diag = dp[i];
      dp[i] = std::min(dp[i] + 1, std::min(diag + (B[j] != A[i]), left + 1));
      diag = new_diag;
      left = dp[i];
    }
  }

  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
