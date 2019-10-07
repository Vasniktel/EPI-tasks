#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

struct Subarray {
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &words) {
  std::unordered_map<string, int> map;

  int len = std::numeric_limits<int>::max(), start = -1, end = -1;
  for (int i = 0, j = 0, n = paragraph.size(); j < n || i < n;) {
    while (j < n && map.size() != words.size()) {
      const auto& word = paragraph[j];
      if (words.find(word) != words.end()) {
        map[word]++;
      }

      j++;
    }

    if (map.size() != words.size()) break;

    if (j - i < len) {
      len = j - i;
      start = i;
      end = j - 1;
    }

    auto it = map.find(paragraph[i]);
    if (it != map.end() && --it->second == 0) {
      map.erase(it);
    }

    i++;
  }

  return {start, end};
}
int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords) {
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&] { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end) {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty()) {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
