#include <string>
#include "test_framework/generic_test.h"
using std::string;

string LookAndSay(int n) {
  string result = "1";

  for (int i = 1; i < n; ++i) {
    string tmp;
    int count = 0;
    char prev = result[0];
    for (char c : result) {
      if (c != prev) {
        tmp += ::std::to_string(count);
        tmp += prev;
        count = 0;
        prev = c;
      }

      count++;
    }

    tmp += ::std::to_string(count);
    tmp += prev;
    result = ::std::move(tmp);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
