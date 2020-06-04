#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;
using std::greater;

vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
  priority_queue<int, vector<int>, greater<>> pq(sequence_begin, sequence_begin + k);
  vector<int> result;

  for (auto it = sequence_begin + k; it != sequence_end; ++it) {
    pq.push(*it);
    result.push_back(pq.top());
    pq.pop();
  }

  while (!pq.empty()) {
    result.push_back(pq.top());
    pq.pop();
  }

  return result;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
