#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<vector<int>> GeneratePascalTriangle(int n) {
  vector<vector<int>> result(n);

  for (int i = 0; i < n; ++i) {
    result[i].resize(i + 1, 1);
    for (int j = i - 1; j > 0; --j) {
      result[i][j] = result[i - 1][j] + result[i - 1][j - 1];
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
