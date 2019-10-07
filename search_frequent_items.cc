#include <iterator>
#include <string>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

// Finds the candidates which may occur > n / k times.
vector<string> SearchFrequentItems(
    int k, vector<string>::const_iterator stream_begin,
    const vector<string>::const_iterator stream_end) {
  std::unordered_map<string, int> map;

  for (auto it = stream_begin; it != stream_end; ++it) {
    map[*it]++;
  }

  auto comp = [](const auto& a, const auto& b) {
    return a->second > b->second;
  };

  std::priority_queue<std::unordered_map<string, int>::iterator, vector<std::unordered_map<string, int>::iterator>, decltype(comp)> pq(comp);
  auto it = map.begin();
  for (int i = 0; i < k; ++i, ++it) {
    pq.push(it);
  }

  for (; it != map.end(); ++it) {
    pq.push(it);
    pq.pop();
  }

  vector<string> result;
  result.reserve(k);

  while (!pq.empty()) {
    result.push_back(pq.top()->first);
    pq.pop();
  }

  return result;
}
vector<string> SearchFrequentItemsWrapper(int k, vector<string>& stream) {
  return SearchFrequentItems(k, begin(stream), end(stream));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "stream"};
  return GenericTestMain(
      args, "search_frequent_items.cc", "search_frequent_items.tsv",
      &SearchFrequentItemsWrapper,
      &UnorderedComparator<std::vector<std::string>>, param_names);
}
