#include <algorithm>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool valid(const string& s) {
  if (s.empty() || s.size() > 3) return false;
  if (s.size() > 1 && s[0] == '0') return false;
  int i = ::std::stoi(s);
  return 0 <= i && i <= 255;
}

vector<string> GetValidIpAddress(const string& s) {
  vector<string> result;

  int n = s.size();
  for (int i = 1; i < 4; ++i) {
    auto a = s.substr(0, i);
    if (valid(a)) {
      for (int j = 1; i + j < n && j < 4; ++j) {
        auto b = s.substr(i, j);
        if (valid(b)) {
          for (int k = 1; i + j + k < n && k < 4; ++k) {
            auto c = s.substr(i + j, k);
            auto d = s.substr(i + j + k);
            if (valid(c) && valid(d)) {
              result.emplace_back(a + '.' + b + '.' + c + '.' + d);
            }
          }
        }
      }
    }
  }

  return result;
}
bool comp(vector<string> expected, vector<string> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return expected == result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress, &comp,
                         param_names);
}
