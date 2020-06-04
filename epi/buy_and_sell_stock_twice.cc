#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

double BuyAndSellStockTwice(const vector<double>& prices) {
  auto result = 0.0;
  int n = prices.size();
  auto min = ::std::numeric_limits<double>::infinity();
  vector<double> first_buy_sell(prices.size(), 0);

  for (int i = 0; i < n; ++i) {
    min = ::std::min(min, prices[i]);
    first_buy_sell[i] = result = ::std::max(result, prices[i] - min);
  }

  auto max = -::std::numeric_limits<double>::infinity();
  for (int i = n - 1; i > 0; i--) {
    max = ::std::max(max, prices[i]);
    result = ::std::max(result, max - prices[i] + first_buy_sell[i - 1]);
  } // [12, 10, 11, 9, 13, 14, 15]

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
