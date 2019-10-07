#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

static const string map[] = {
    "0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"
};

void Recur(const string& num, int i, vector<string>& ans, string& buff) {
  if (i == num.size()) {
    ans.push_back(buff);
    return;
  }

  for (char c : map[num[i] - '0']) {
    buff += c;
    Recur(num, i + 1, ans, buff);
    buff.pop_back();
  }
}

vector<string> PhoneMnemonic(const string& phone_number) {
  vector<string> result;
  string buff;
  Recur(phone_number, 0, result, buff);
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         &UnorderedComparator<std::vector<std::string>>,
                         param_names);
}
