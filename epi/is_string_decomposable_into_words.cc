#include <string>
#include <unordered_set>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

struct HashedString {
  string s;
  uint64_t hash;
};

uint64_t hash(const string& s) {
  uint64_t result = 0;

  for (char c : s) {
    result = result * 31 + c;
  }

  return result;
}

bool recur(const string& s, int i, const vector<HashedString>& vec, vector<string>& ans, vector<int>& memo) {
  if (i == s.size()) return true;
  if (memo[i] != -1) return memo[i];

  uint64_t cumm = 0, k = 0;
  for (int j = i, n = s.size(); j < n; ++j) {
    cumm = cumm * 31 + s[j];
    while (k < vec.size() && vec[k].s.size() == j - i + 1) {
      if (vec[k].hash == cumm) {
        ans.push_back(vec[k].s);
        if (recur(s, j + 1, vec, ans, memo)) return memo[i] = true;
        ans.pop_back();
      }
      k++;
    }

    if (k == vec.size()) break;
    assert(vec[k].s.size() > j - i + 1);
  }

  return memo[i] = false;
}

vector<string> DecomposeIntoDictionaryWords(
    const string& domain, const unordered_set<string>& dictionary) {
  vector<HashedString> vec;
  vec.reserve(dictionary.size());

  for (const auto& word : dictionary) {
    vec.push_back({word, hash(word)});
  }

  std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
    return a.s.size() < b.s.size();
  });

  vector<string> result;
  result.reserve(dictionary.size());
  vector<int> memo(domain.size(), -1);
  recur(domain, 0, vec, result, memo);
  return result;
}
void DecomposeIntoDictionaryWordsWrapper(
    TimedExecutor& executor, const string& domain,
    const unordered_set<string>& dictionary, bool decomposable) {
  vector<string> result = executor.Run(
      [&] { return DecomposeIntoDictionaryWords(domain, dictionary); });
  if (!decomposable) {
    if (!result.empty()) {
      throw TestFailure("domain is not decomposable");
    }
    return;
  }

  if (std::any_of(std::begin(result), std::end(result),
                  [&](const std::string& s) { return !dictionary.count(s); })) {
    throw TestFailure("Result uses words not in dictionary");
  }

  if (std::accumulate(std::begin(result), std::end(result), string()) !=
      domain) {
    throw TestFailure("Result is not composed into domain");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "domain", "dictionary",
                                       "decomposable"};
  return GenericTestMain(args, "is_string_decomposable_into_words.cc",
                         "is_string_decomposable_into_words.tsv",
                         &DecomposeIntoDictionaryWordsWrapper,
                         DefaultComparator{}, param_names);
}
