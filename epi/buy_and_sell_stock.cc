#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  auto result = 0.0;
  auto min = ::std::numeric_limits<double>::infinity();
  
  for (auto val : prices) {
    min = ::std::min(min, val);
    result = ::std::max(result, val - min);
  }
  
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
