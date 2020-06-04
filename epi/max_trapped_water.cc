#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int GetMaxTrappedWater(const vector<int>& heights) {
  int lo = 0, hi = heights.size() - 1;
  int result = 0;
  while (lo < hi) {
    result = std::max(result, std::min(heights[lo], heights[hi]) * (hi - lo));
    if (heights[lo] < heights[hi]) lo++;
    else hi--;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "max_trapped_water.cc", "max_trapped_water.tsv",
                         &GetMaxTrappedWater, DefaultComparator{}, param_names);
}
