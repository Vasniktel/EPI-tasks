#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> arr) {
  ::std::reverse(arr.begin(), arr.end());
  int carry = 1;
  for (int i = 0, n = arr.size(); i < n && carry != 0; ++i) {
    arr[i] += carry;
    carry = arr[i] / 10;
    arr[i] %= 10;
  }
  
  if (carry != 0) arr.push_back(carry);
  ::std::reverse(arr.begin(), arr.end());
  return arr;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
