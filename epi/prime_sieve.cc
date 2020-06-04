#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  ::std::deque<bool> primes(n + 1, true);
  vector<int> result;
  primes[1] = false;

  for (int i = 2; i <= n; ++i) {
    if (primes[i]) {
      result.push_back(i);
      for (auto j = static_cast<long long>(i) * i; j <= n; j += i) {
        primes[j] = false;
      }
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
