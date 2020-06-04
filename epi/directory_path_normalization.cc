#include <string>
#include "test_framework/generic_test.h"
using std::string;
string ShortestEquivalentPath(const string& path) {
  if (path.empty()) return "";

  using namespace std::string_literals;
  ::std::vector<string> dirs;

  ::std::istringstream iss(path);
  for (string s; ::std::getline(iss, s, '/');) {
    if (s == ".") continue;
    if (s.empty()) continue;
    if (s == "..") {
      if (dirs.empty() || dirs.back() == "..") {
        dirs.emplace_back(::std::move(s));
      } else {
        dirs.pop_back();
      }
    } else {
      dirs.emplace_back(::std::move(s));
    }
  }

  string result;
  for (int i = 0, n = dirs.size(); i < n; ++i) {
    if (i != 0) result += '/';
    result += dirs[i];
  }

  return path.front() == '/' ? '/' + result : result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
