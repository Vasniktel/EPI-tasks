#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
int NumberOfWays(int n, int m) {
  vector<int> dp(std::min(n, m));
  dp.front() = 1;
  
  for (int i = 0; i < std::max(m, n); ++i) {
    for (int j = 1; j < dp.size(); ++j) {
      dp[j] += dp[j - 1];
    }
  }
  
  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
