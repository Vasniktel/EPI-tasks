#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using ::std::pair;
using ::std::priority_queue;
vector<int> SortKIncreasingDecreasingArray(const vector<int>& A) {
  auto comp = [&A](const auto& a, const auto& b) {
    return A[a.first] > A[b.first];
  };

  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> seqs(comp);

  bool increasing = true;
  for (int i = 0, n = A.size(); i < n; increasing = !increasing) {
    int j;
    for (j = i + 1; j < n; ++j) {
      if (A[j] > A[j - 1] != increasing) break;
    }

    if (increasing) seqs.emplace(i, j);
    else seqs.emplace(j - 1, i - 1);

    i = j;
  }

  vector<int> result(A.size());
  for (int& val : result) {
    auto top = seqs.top();
    seqs.pop();
    val = A[top.first];
    if (top.first > top.second) top.first--;
    else top.first++;
    if (top.first != top.second) {
      seqs.push(top);
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
                         "sort_increasing_decreasing_array.tsv",
                         &SortKIncreasingDecreasingArray, DefaultComparator{},
                         param_names);
}
