#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int MinimumTotalWaitingTime(vector<int> service_times) {
  std::sort(service_times.begin(), service_times.end());

  int result = 0, prev = 0;
  for (int i = 0, n = service_times.size(); i < n - 1; ++i) {
    prev += service_times[i];
    result += prev;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"service_times"};
  return GenericTestMain(args, "minimum_waiting_time.cc",
                         "minimum_waiting_time.tsv", &MinimumTotalWaitingTime,
                         DefaultComparator{}, param_names);
}
