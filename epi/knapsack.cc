#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Item {
  int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
  vector<int> prev(capacity + 1);
  auto curr = prev;

  for (const auto& item : items) {
    for (int j = 0; j <= capacity; ++j) {
      if (item.weight > j) {
        curr[j] = prev[j];
      } else {
        curr[j] = std::max(prev[j - item.weight] + item.value, prev[j]);
      }
    }

    prev = move(curr);
    curr.assign(capacity + 1, 0);
  }

  return prev.back();
}
template <>
struct SerializationTraits<Item> : UserSerTraits<Item, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
