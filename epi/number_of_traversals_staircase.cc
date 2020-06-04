#include "test_framework/generic_test.h"

int NumberOfWaysToTop(int top, int maximum_step) {
  std::queue<int> q({1});

  int sum = 1;
  for (int i = 1; i < maximum_step; ++i) {
    q.push(sum);
    sum += q.back();
  }

  for (int i = maximum_step; i < top; ++i) {
    q.push(sum);
    sum -= q.front();
    q.pop();
    sum += q.back();
  }

  return sum;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"top", "maximum_step"};
  return GenericTestMain(args, "number_of_traversals_staircase.cc",
                         "number_of_traversals_staircase.tsv",
                         &NumberOfWaysToTop, DefaultComparator{}, param_names);
}
