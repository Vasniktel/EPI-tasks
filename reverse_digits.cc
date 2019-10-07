#include "test_framework/generic_test.h"
long long Reverse(int x) {
  int sign = x < 0 ? -1 : 1;
  auto result = 0LL;
  x = abs(x);
  
  while (x > 0) {
    int digit = x % 10;
    result = result * 10 + digit;
    x /= 10;
  }
  
  return sign * result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
