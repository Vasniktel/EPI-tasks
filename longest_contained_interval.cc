#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int LongestContainedRange(const vector<int>& A) {
  if (A.empty()) return 0;

  std::unordered_set<int> set(A.begin() + 1, A.end());

  int first = A.front(), last = A.front(), result = 0;
  while (!set.empty()) {
    auto a = set.find(first - 1);
    auto b = set.find(last + 1);

    if (a == set.end() && b == set.end()) {
      result = std::max(result, last - first + 1);
      first = last = *set.begin();
      set.erase(set.begin());
      continue;
    }

    if (a != set.end()) {
      first--;
      set.erase(a);
    }

    if (b != set.end()) {
      last++;
      set.erase(b);
    }
  }

  return std::max(result, last - first + 1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
