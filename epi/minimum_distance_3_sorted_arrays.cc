#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int FindClosestElementsInSortedArrays(
    const vector<vector<int>>& sorted_arrays) {
  assert(!sorted_arrays.empty());

  auto comp = [&sorted_arrays](const auto& a, const auto& b) {
    return *a.first < *b.first;
  };

  std::multiset<std::pair<vector<int>::const_iterator, vector<int>::const_iterator>, decltype(comp)> pq(comp);

  for (const auto& arr : sorted_arrays) {
    assert(!arr.empty());
    pq.emplace(arr.cbegin(), arr.cend());
  }

  int result = std::numeric_limits<int>::max();
  while (true) {
    auto min_it = *pq.begin();
    auto max_it = *pq.rbegin();
    pq.erase(pq.begin());
    int min = *min_it.first;
    int max = *max_it.first;
    result = std::min(result, max - min);
    ++min_it.first;
    if (min_it.first == min_it.second) break;
    pq.insert(min_it);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "minimum_distance_3_sorted_arrays.cc",
                         "minimum_distance_3_sorted_arrays.tsv",
                         &FindClosestElementsInSortedArrays,
                         DefaultComparator{}, param_names);
}
