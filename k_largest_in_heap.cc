#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;

vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
  if (A.empty()) return {};

  auto comp = [&A](int a, int b) {
    return A[a] < A[b];
  };

  priority_queue<int, vector<int>, decltype(comp)> pq(comp, {0});
  vector<int> result;
  result.reserve(k);

  int n = A.size();
  while (!pq.empty() && result.size() != k) {
    int top = pq.top(); pq.pop();
    result.push_back(A[top]);
    if (top * 2 + 1 < n) pq.push(top * 2 + 1);
    if (top * 2 + 2 < n) pq.push(top * 2 + 2);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
