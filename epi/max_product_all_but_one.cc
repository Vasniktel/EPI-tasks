#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int FindBiggestNMinusOneProduct(const vector<int>& A) {
  int zeros = 0, neg = 0;

  for (int val : A) {
    if (val == 0) zeros++;
    else if (val < 0) neg++;
  }

  if (zeros > 1) return 0;
  if (zeros == 1 && (neg & 1) != 0) return 0;
  if (zeros == 1) {
    int result = 1;
    for (int val : A) {
      if (val != 0) result *= val;
    }

    return result;
  }

  if (neg & 1) {
    int result = 1;
    int min = 0, val = std::numeric_limits<int>::min();
    for (int i = 0; i < A.size(); ++i) {
      if (A[i] > val && A[i] < 0) min = i, val = A[i];
    }

    for (int i = 0; i < A.size(); ++i) {
      if (i != min) result *= A[i];
    }

    return result;
  } else {
    int result = 1;
    int min = 0, val = std::numeric_limits<int>::max();
    for (int i = 0; i < A.size(); ++i) {
      if (A[i] < val && A[i] > 0) min = i, val = A[i];
    }

    for (int i = 0; i < A.size(); ++i) {
      if (i != min) result *= A[i];
    }

    return result;
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "max_product_all_but_one.cc", "max_product_all_but_one.tsv",
      &FindBiggestNMinusOneProduct, DefaultComparator{}, param_names);
}
