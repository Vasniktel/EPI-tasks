#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  auto odd = make_shared<ListNode<int>>(), curr_odd = odd;
  auto even = make_shared<ListNode<int>>(), curr_even = even;

  auto node = L;
  for (bool flip = true; node; flip = !flip, node = node->next) {
    if (flip) {
      curr_even->next = node;
      curr_even = curr_even->next;
    } else {
      curr_odd->next = node;
      curr_odd = curr_odd->next;
    }
  }

  curr_even->next = odd->next;
  curr_odd->next = nullptr;
  return even->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
