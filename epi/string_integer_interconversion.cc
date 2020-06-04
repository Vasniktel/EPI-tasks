#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(long long x) {
  if (x == 0) return "0";

  bool neg = x < 0;
  x = llabs(x);
  string result;

  while (x != 0) {
    result += (x % 10) + '0';
    x /= 10;
  }

  if (neg) result += '-';
  ::std::reverse(result.begin(), result.end());
  return result;
}
int StringToInt(const string& s) {
  const char* data = s.data();

  int sign = *data == '-' ? -1 : 1;
  if (*data == '-') data++;

  int result = 0;
  for (; *data; data++) {
    result = result * 10 + (*data - '0');
  }

  return sign * result;
}
void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
