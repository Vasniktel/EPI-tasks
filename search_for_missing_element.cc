#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct DuplicateAndMissing {
  int duplicate, missing;
};

DuplicateAndMissing FindDuplicateMissing(const vector<int>& A) {
  int xor_n = 0;
  for (int i = 0, n = A.size(); i < n; ++i) {
    xor_n ^= i ^ A[i];
  }

  int mask = xor_n & ~(xor_n - 1);
  int el = 0;
  for (int i = 0, n = A.size(); i < n; ++i) {
    if (i & mask) el ^= i;
    if (A[i] & mask) el ^= A[i];
  }

  if (std::find(A.begin(), A.end(), el) == A.end()) return {xor_n ^ el, el};
  return {el, xor_n ^ el};
}
template <>
struct SerializationTraits<DuplicateAndMissing>
    : UserSerTraits<DuplicateAndMissing, int, int> {};

bool operator==(const DuplicateAndMissing& lhs,
                const DuplicateAndMissing& rhs) {
  return std::tie(lhs.duplicate, lhs.missing) ==
         std::tie(rhs.duplicate, rhs.missing);
}

std::ostream& operator<<(std::ostream& out, const DuplicateAndMissing& x) {
  return out << "duplicate: " << x.duplicate << ", missing: " << x.missing;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "search_for_missing_element.cc", "find_missing_and_duplicate.tsv",
      &FindDuplicateMissing, DefaultComparator{}, param_names);
}
