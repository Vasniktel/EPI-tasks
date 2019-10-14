#include <string>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;

bool valid(const string& a, const string& b) {
  if (a.size() != b.size()) return false;
  int count = 0;

  for (int i = 0, n = a.size(); i < n; ++i) {
    if (a[i] != b[i]) count++;
    if (count > 1) return false;
  }

  return count == 1;
}

// Uses BFS to find the least steps of transformation.
int TransformString(unordered_set<string> D, const string& s, const string& t) {
  struct WordAndPath {
    string word;
    int path;

    WordAndPath(string word, int path)
    : word(std::move(word)),
      path(path)
    {}
  };

  std::queue<WordAndPath> q({{s, 0}});
  D.erase(s);

  while (!q.empty()) {
    if (q.front().word == t) return q.front().path;

    for (auto it = D.begin(); it != D.end();) {
      if (valid(q.front().word, *it)) {
        auto visited = it;
        ++it;
        q.emplace(*std::make_move_iterator(visited), q.front().path + 1);
        D.erase(visited);
      } else {
        ++it;
      }
    }

    q.pop();
  }

  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
