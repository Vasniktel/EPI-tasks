#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

double BuyAndSellStockKTimes(const vector<double>& prices, int k) {
  if (prices.empty()) return 0;
  vector<double> dp(prices.size());

  auto min = prices[0];
  for (int i = 1, n = prices.size(); i < n; ++i) {
    min = std::min(min, prices[i]);
    dp[i] = std::max(prices[i] - min, dp[i - 1]);
  }

  for (int i = 1; i < k; ++i) {
    auto max = -prices[i];
    for (int j = 1, n = dp.size(); j < n; ++j) {
      auto prev = dp[j];
      dp[j] = std::max(dp[j - 1], prices[j] + max);
      max = std::max(max, -prices[j] + prev);
    }
  }

  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices", "k"};
  return GenericTestMain(
      args, "buy_and_sell_stock_k_times.cc", "buy_and_sell_stock_k_times.tsv",
      &BuyAndSellStockKTimes, DefaultComparator{}, param_names);
}
