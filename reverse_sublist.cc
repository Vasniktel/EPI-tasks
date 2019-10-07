#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  auto head = make_shared<ListNode<int>>(0, L);
  auto before_first = head, curr = head;

  for (int i = 0; i < start; ++i) {
    before_first = curr;
    curr = curr->next;
  }

  for (int i = start; i < finish; ++i) {
    auto tmp = curr->next;
    curr->next = tmp->next;
    tmp->next = before_first->next;
    before_first->next = tmp;
  }

  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
