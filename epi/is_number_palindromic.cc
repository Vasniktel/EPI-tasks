#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int y) {
  auto result = 0LL;
  int x = abs(y);

  while (x > 0) {
    int digit = x % 10;
    result = result * 10 + digit;
    x /= 10;
  }

  return result == y;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
