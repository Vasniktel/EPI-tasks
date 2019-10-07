#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
int RomanToInteger(const string& s) {
  static const ::std::unordered_map<char, int> map = {
      {'I', 1},
      {'V', 5},
      {'X', 10},
      {'L', 50},
      {'C', 100},
      {'D', 500},
      {'M', 1000}
  };

  int result = 0;
  for (int i = 0, n = s.size(); i < n;) {
    int sum = 0, top = map.at(s[i]);

    for (i++; i < n && map.at(s[i]) > top; top = map.at(s[i++])) {
      sum += top;
    }

    result += top - sum;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
                         &RomanToInteger, DefaultComparator{}, param_names);
}
