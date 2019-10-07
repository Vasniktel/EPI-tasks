#include <string>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

constexpr int k = 31;

int64_t hash(const string& s, int n) {
  int64_t result = 0;

  for (int i = 0; i < n; ++i) {
    result = result * k + s[i];
  }

  return result;
}
// TODO
vector<int> FindAllSubstrings(const string& s, const vector<string>& words) {
  if (words.empty()) return {};

  std::unordered_map<int64_t, int> hashes;

  int size = words.front().size();
  for (const auto& word : words) {
    ++hashes[hash(word, size)];
  }

  vector<std::pair<int64_t, bool>> idxs(s.size(), {0, false});
  int64_t hash_val = hash(s, size), powed = pow(k, size - 1);
  for (int i = size, n = s.size(); i <= n; ++i) {
    if (hashes.find(hash_val) != hashes.end()) {
      idxs[i - size] = {hash_val, true};
    }

    hash_val -= s[i - size] * powed;
    hash_val *= k;
    hash_val += s[i];
  }

  vector<int> result;
  for (int i = 0, n = idxs.size(); i < n; ++i) {
    std::unordered_map<int64_t, int> map;

    for (int j = i; j < n && idxs[j].second && map != hashes; j += size) {
      ++map[idxs[j].first];
    }

    if (map == hashes) result.push_back(i);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s", "words"};
  return GenericTestMain(args, "string_decompositions_into_dictionary_words.cc",
                         "string_decompositions_into_dictionary_words.tsv",
                         &FindAllSubstrings, DefaultComparator{}, param_names);
}
