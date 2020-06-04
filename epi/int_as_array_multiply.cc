#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> Multiply(vector<int> num1, vector<int> num2) {
  int sign = num1[0] > 0 ^ num2[0] > 0 ? -1 : 1;
  num1[0] = abs(num1[0]);
  num2[0] = abs(num2[0]);
  vector<int> result(num1.size() + num2.size(), 0);

  for (int i = num1.size() - 1; i >= 0; --i) {
    for (int j = num2.size() - 1; j >= 0; --j) {
      result[i + j + 1] += num1[i] * num2[j];
      result[i + j] += result[i + j + 1] / 10;
      result[i + j + 1] %= 10;
    }
  }

  result = {::std::find_if_not(result.begin(), result.end(), [](int v) { return v == 0; }), result.end()};
  if (result.empty()) return {0};
  result[0] *= sign;
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
