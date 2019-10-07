#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  auto head = make_shared<ListNode<int>>();
  auto curr = head;

  while (curr && (L1 || L2)) {
    shared_ptr<ListNode<int>>* node;
    if (!L1) node = &L2;
    else if (!L2) node = &L1;
    else if (L2->data < L1->data) node = &L2;
    else node = &L1;

    curr->next = *node;
    curr = curr->next;
    *node = (*node)->next;
  }

  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
