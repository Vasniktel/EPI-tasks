#include <string>
#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
  if (b1 == b2) return num_as_string;

  static const char num_to_char[] = {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
  };

  bool neg = num_as_string[0] == '-';
  auto dec = 0ull;

  for (int i = neg, n = num_as_string.size(); i < n; ++i) {
    int num = isdigit(num_as_string[i]) ? num_as_string[i] - '0' : num_as_string[i] - 'A' + 10;
    dec = dec * b1 + num;
  }

  string result;
  do {
    result += num_to_char[dec % b2];
    dec /= b2;
  } while (dec != 0);

  if (neg) result += '-';
  ::std::reverse(result.begin(), result.end());
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
