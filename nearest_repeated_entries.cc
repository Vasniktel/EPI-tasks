#include <string>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
  std::unordered_map<string, int> map;

  int result = std::numeric_limits<int>::max();
  for (int i = 0, n = paragraph.size(); i < n; ++i) {
    if (map.find(paragraph[i]) != map.end()) {
      result = std::min(result, i - map[paragraph[i]]);
    }

    map[paragraph[i]] = i;
  }

  return result == std::numeric_limits<int>::max() ? -1 : result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
