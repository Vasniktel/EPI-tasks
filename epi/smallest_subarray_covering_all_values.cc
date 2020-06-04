#include <string>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using std::unordered_map;

struct Subarray {
  // Represent subarray by starting and ending indices, inclusive.
  int start, end;
};

Subarray FindSmallestSequentiallyCoveringSubset(
    const vector<string>& paragraph, const vector<string>& keywords) {
  std::unordered_map<string, int> map;
  for (int i = 0, n = keywords.size(); i < n; ++i) {
    map[keywords[i]] = i;
  }

  vector<vector<int>> idxs(keywords.size());
  for (int i = static_cast<int>(paragraph.size()) - 1; i >= 0; --i) {
    auto it = map.find(paragraph[i]);
    if (it == map.end()) continue;
    idxs[it->second].push_back(i);
  }

  if (idxs.front().empty()) return {-1, -1};
  for (int i = 1, n = idxs.size(); i < n; ++i) {
    auto& curr = idxs[i];
    auto it = std::upper_bound(curr.begin(), curr.end(), idxs[i - 1].back(), std::greater<>{});
    curr.erase(it, curr.end());
    if (curr.empty()) return {-1, -1};
  }

  int len = std::numeric_limits<int>::max(), start = -1, end = -1;
  for (; !idxs.front().empty(); idxs.front().pop_back()) {
    for (int i = 1, n = idxs.size(); i < n && idxs[i].back() < idxs[i - 1].back(); ++i) {
      auto& curr = idxs[i];
      auto it = std::upper_bound(curr.begin(), curr.end(), idxs[i - 1].back(), std::greater<>{});
      curr.erase(it, curr.end());
      if (curr.empty()) return {start, end};
    }
    
    int new_len = idxs.back().back() - idxs.front().back();
    if (new_len < len) {
      len = new_len;
      start = idxs.front().back();
      end = idxs.back().back();
    }
  }
  
  return {start, end};
}
int FindSmallestSequentiallyCoveringSubsetWrapper(
    TimedExecutor& executor, const vector<string>& paragraph,
    const vector<string>& keywords) {
  auto result = executor.Run([&] {
    return FindSmallestSequentiallyCoveringSubset(paragraph, keywords);
  });

  int kw_idx = 0;
  if (result.start < 0) {
    throw TestFailure("Subarray start index is negative");
  }
  int para_idx = result.start;

  while (kw_idx < keywords.size()) {
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Not all keywords are in the generated subarray");
    }
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Subarray end index exceeds array size");
    }
    if (paragraph[para_idx] == keywords[kw_idx]) {
      kw_idx++;
    }
    para_idx++;
  }
  return result.end - result.start + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_all_values.cc",
                         "smallest_subarray_covering_all_values.tsv",
                         &FindSmallestSequentiallyCoveringSubsetWrapper,
                         DefaultComparator{}, param_names);
}
