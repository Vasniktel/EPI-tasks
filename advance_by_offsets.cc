#include <vector>
#include <deque>
#include "test_framework/generic_test.h"
using std::vector;
bool CanReachEnd(const vector<int>& max_advance_steps) {
  assert(!max_advance_steps.empty());
  int n = max_advance_steps.size(), max = 0;

  for (int i = 0; i <= max && max < n - 1; ++i) {
    max = ::std::max(max, i + max_advance_steps[i]);
  }

  return max >= n - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
