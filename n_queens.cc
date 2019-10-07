#include <algorithm>
#include <iterator>
#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

void recur(int n, vector<vector<int>>& ans, vector<int>& queens, vector<std::unordered_set<int>>& invalid) {
  if (n == invalid.size() && queens.size() == invalid.size()) return ans.push_back(queens);
  if (n == invalid.size()) return;

  for (int i = 0, len = invalid.size(); i < len; ++i) {
    if (!invalid[n].count(i)) {
      queens.push_back(i);
      for (int j = n + 1; j < len; ++j) {
        if (i - (j - n) >= 0) invalid[j].insert(i - j - n);
        if (i + (j - n) < len) invalid[j].insert(i + j - n);
        invalid[j].insert(i);
      }
      recur(n + 1, ans, queens, invalid);
      for (int j = n + 1; j < len; ++j) {
        if (j >= 0) invalid[j].erase(i - j - n);
        if (j < len) invalid[j].erase(i + j - n);
        invalid[j].erase(i);
      }
      queens.pop_back();
    }
  }
}

vector<vector<int>> NQueens(int n) {
  vector<vector<int>> result;
  vector<std::unordered_set<int>> invalid(n);
  vector<int> queens;
  recur(0, result, queens, invalid);
  return result;
}
bool Comp(vector<vector<int>>& a, vector<vector<int>>& b) {
  std::sort(std::begin(a), std::end(a));
  std::sort(std::begin(b), std::end(b));
  return a == b;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens, &Comp,
                         param_names);
}
