#include <string>
#include "test_framework/generic_test.h"
using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
int RabinKarp(const string &t, const string &s) {
  if (s.size() > t.size()) return -1;
  
  auto hash_s = 0u;
  for (char c : s) {
    hash_s = hash_s * 31 + c;
  }

  auto hash_t = 0u;
  for (int i = 0, n = s.size(); i < n; ++i) {
    hash_t = hash_t * 31 + t[i];
  }

  long long p = pow(31, s.size() - 1);
  for (int i = s.size(), n = t.size(); i <= n; ++i) {
    if (hash_t == hash_s) return i - s.size();
    hash_t -= t[i - s.size()] * p;
    hash_t = hash_t * 31 + t[i];
  }
  
  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};
  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}
