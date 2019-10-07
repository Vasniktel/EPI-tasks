#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

// TODO: figure out an alternative solution
int MaximumRevenue(const vector<int>& coins) {
  auto dp = coins;
  auto sum = coins;
  // dp[0][coins.size() - 1] = result
  // dp[i][j] = max(coins[i], coins[j]) + dp[i + 1][j - 1]
  // dp[i][i] = coins[i]

  int n = coins.size();
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      dp[j] = std::max(coins[i] + sum[j] - dp[j], coins[j] + sum[j - 1] - dp[j - 1]);
      sum[j] = sum[j - 1] + coins[j];
    }
  }

  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"coins"};
  return GenericTestMain(args, "picking_up_coins.cc", "picking_up_coins.tsv",
                         &MaximumRevenue, DefaultComparator{}, param_names);
}
