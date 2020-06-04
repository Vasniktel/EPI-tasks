#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int recur(const string& s, int& i) {
  int result = 0, count = 0;

  while (i < s.size() && s[i] == '(') {
    i++;
    int inner = recur(s, i);
    if (s[i] == ')') inner += 2;
    re
  }

  return result;
}

int LongestMatchingParentheses(const string& s) {
  int i = 0;
  return recur(s, i);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "longest_substring_with_matching_parentheses.cc",
                         "longest_substring_with_matching_parentheses.tsv",
                         &LongestMatchingParentheses, DefaultComparator{},
                         param_names);
}
