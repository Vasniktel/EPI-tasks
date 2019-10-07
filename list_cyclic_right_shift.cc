#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
  if (!L) return nullptr;
  int n = 1;
  auto last = L;
  for (; last->next; last = last->next) {
    n++;
  }

  k %= n;
  if (k == 0) return L;

  auto start = L;
  for (int i = 1; i < n - k; ++i) {
    start = start->next;
  }

  auto result = start->next;
  start->next = nullptr;
  last->next = L;
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
