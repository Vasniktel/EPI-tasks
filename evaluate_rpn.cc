#include <string>
#include "test_framework/generic_test.h"
using std::string;
int Evaluate(const string& expression) {
#define OP(op) \
    do { \
      int b = val.back(); \
      val.pop_back(); \
      val.back() = val.back() op b; \
    } while (false)

  ::std::vector<int> val;
  ::std::istringstream iss(expression);

  for (string s; ::std::getline(iss, s, ',');) {
    switch (s[0]) {
      case '+': OP(+); break;
      case '-': OP(-); break;
      case '*': OP(*); break;
      case '/': OP(/); break;
      default: val.push_back(::std::stoi(s));
    }
  }

  return val.front();
#undef OP
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
