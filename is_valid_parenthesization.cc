#include <string>
#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
  ::std::vector<int> stack;

  for (char c : s) {
    char check;
    switch (c) {
      case '}': check = '{'; break;
      case ')': check = '('; break;
      case ']': check = '['; break;
      default:
        stack.push_back(c);
        continue;
    }

    if (stack.empty() || stack.back() != check) {
      return false;
    }

    stack.pop_back();
  }

  return stack.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
