#include <iterator>
#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {
  vector<int> result, idx;

  int i = 0;
  for (auto it = sequence_begin; it != sequence_end; ++it, ++i) {
    while (!result.empty() && result.back() <= *it) {
      result.pop_back();
      idx.pop_back();
    }

    result.push_back(*it);
    idx.push_back(i);
  }

  ::std::reverse(idx.begin(), idx.end());
  return idx;
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
