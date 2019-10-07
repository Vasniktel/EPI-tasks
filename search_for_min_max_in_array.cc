#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
struct MinMax {
  int smallest, largest;
};

MinMax FindMinMax(const vector<int>& A) {
  assert(!A.empty());
  if (A.size() == 1) return {A[0], A[0]};

  int min = std::min(A[0], A[1]);
  int max = std::max(A[0], A[1]);

  for (int i = 2, n = A.size(); i < n; ++i) {
    if (A[i] < min) {
      min = A[i];
    } else if (A[i] > max) {
      max = A[i];
    }
  }

  return {min, max};
}
template <>
struct SerializationTraits<MinMax> : UserSerTraits<MinMax, int, int> {};

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_for_min_max_in_array.cc",
                         "search_for_min_max_in_array.tsv", &FindMinMax,
                         DefaultComparator{}, param_names);
}
