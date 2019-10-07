#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* str) {
  auto& s = *str;

  ::std::reverse(s.begin(), s.end());
  for (int i = 0, j = 0, n = s.size(); i < n; ++j) {
    if (s[j] == ' ' || s[j] == '\0') {
      ::std::reverse(s.begin() + i, s.begin() + j);
      i = j + 1;
    }
  }
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
