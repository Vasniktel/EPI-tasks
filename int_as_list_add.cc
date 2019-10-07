#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> L1,
                                        shared_ptr<ListNode<int>> L2) {
  auto head = make_shared<ListNode<int>>(), curr = head;

  int carry = 0;
  while (L1 || L2) {
    int val = carry;
    if (L1) val += L1->data;
    if (L2) val += L2->data;

    carry = val / 10;
    curr->next = make_shared<ListNode<int>>(val % 10);
    curr = curr->next;
    if (L1) L1 = L1->next;
    if (L2) L2 = L2->next;
  }

  if (carry != 0) curr->next = make_shared<ListNode<int>>(carry);
  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "int_as_list_add.cc", "int_as_list_add.tsv",
                         &AddTwoNumbers, DefaultComparator{}, param_names);
}
