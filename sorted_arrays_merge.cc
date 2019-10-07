#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;
using ::std::greater;
using ::std::deque;
using ::std::back_inserter;
using ::std::make_heap;
using ::std::push_heap;
using ::std::pop_heap;

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  vector<deque<int>> pq;
  pq.reserve(sorted_arrays.size());
  
  for (const auto& arr : sorted_arrays) {
    pq.emplace_back(arr.begin(), arr.end());
  }

  make_heap(pq.begin(), pq.end(), greater<>{});
  
  vector<int> result;
  while (!pq.empty()) {
    pop_heap(pq.begin(), pq.end(), greater<>{});
    auto& top = pq.back();
    result.push_back(top.front());
    top.pop_front();
    if (top.empty()) pq.pop_back();
    else push_heap(pq.begin(), pq.end(), greater<>{});
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
