#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include <random>
#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::iota;
using std::vector;
// Returns a random k-sized subset of {0, 1, ..., n - 1}.
vector<int> RandomSubset(int n, int k) {
  ::std::unordered_map<int, int> map;
  ::std::mt19937 e(::std::random_device{}());

  for (int i = 0; i < k; ++i) {
    int j = ::std::uniform_int_distribution<>(i, n - 1)(e);
    auto a = map.find(i), b = map.find(j), end = map.end();
    if (a == end && b == end) map[i] = j, map[j] = i;
    else if (a == end && b != end) map[i] = b->second, b->second = i;
    else if (a != end && b == end) map[j] = a->second, a->second = j;
    else ::std::swap(map[i], map[j]);
  }

  vector<int> ans(k);
  for (int i = 0; i < k; ++i) {
    ans[i] = map[i];
  }

  return ans;
}
bool RandomSubsetRunner(TimedExecutor& executor, int n, int k) {
  vector<vector<int>> results;

  executor.Run([&] {
    std::generate_n(back_inserter(results), 100000,
                    std::bind(RandomSubset, n, k));
  });

  int total_possible_outcomes = BinomialCoefficient(n, k);
  vector<int> A(n);
  iota(begin(A), end(A), 0);
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(n, k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, n, k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSubsetWrapper(TimedExecutor& executor, int n, int k) {
  RunFuncWithRetries(bind(RandomSubsetRunner, std::ref(executor), n, k));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "n", "k"};
  return GenericTestMain(args, "random_subset.cc", "random_subset.tsv",
                         &RandomSubsetWrapper, DefaultComparator{},
                         param_names);
}
