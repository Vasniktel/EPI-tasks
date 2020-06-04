#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int CalculateLargestRectangle(const vector<int>& heights) {
  std::stack<int> val, left, size;

  for (int x : heights) {
    int count = 0, max = 0;
    while (!val.empty() && val.top() >= x) {
      count += size.top();                   size.pop();
      max = std::max(max, left.top());       left.pop();
      max = std::max(max, val.top() * count); val.pop();
    }

    val.push(x);
    left.push(max);
    size.push(count + 1);
  }

  int max = 0, count = 0;
  while (!val.empty()) {
    count += size.top();                   size.pop();
    max = std::max(max, left.top());       left.pop();
    max = std::max(max, val.top() * count); val.pop();
  }

  return max;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "largest_rectangle_under_skyline.cc",
                         "largest_rectangle_under_skyline.tsv",
                         &CalculateLargestRectangle, DefaultComparator{},
                         param_names);
}
