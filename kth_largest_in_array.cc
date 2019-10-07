#include <vector>
#include <random>
#include "test_framework/generic_test.h"
using std::vector;

int part(vector<int>& arr, int lo, int hi) {
  std::mt19937 e(std::random_device{}());
  int idx = std::uniform_int_distribution<>{lo, hi}(e);
  std::swap(arr[idx], arr[hi]);
  int pivot = hi;

  while (true) {
    while (arr[lo] >  arr[pivot]) lo++;
    while (arr[hi] <= arr[pivot]) hi--;

    if (lo > hi) break;
    std::swap(arr[lo], arr[hi]);
  }

  std::swap(arr[pivot], arr[lo]);
  return lo;
}

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
  auto& arr = *A_ptr;
  assert(!arr.empty());

  int lo = 0, hi = arr.size() - 1;
  while (lo <= hi) {
    int idx = part(arr, lo, hi);
    if (idx == k - 1) return arr[idx];
    if (idx >  k - 1) hi = idx - 1;
    else lo = idx + 1;
  }

  return arr[lo];
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
