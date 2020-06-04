#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> reverse(shared_ptr<ListNode<int>> node) {
  auto head = make_shared<ListNode<int>>();

  while (node) {
    auto tmp = node->next;
    node->next = head->next;
    head->next = node;
    node = tmp;
  }

  return head->next;
}

shared_ptr<ListNode<int>> ZippingLinkedList(
    const shared_ptr<ListNode<int>>& L) {
  if (!L) return nullptr;
  auto slow = L, fast = L->next;

  for (bool flip = false; fast; flip = !flip) {
    fast = fast->next;
    if (flip) slow = slow->next;
  }

  auto next = reverse(slow->next);
  slow->next = nullptr;

  auto head = make_shared<ListNode<int>>();
  auto first = L, last = next, curr = head;
  for (bool flip = false; first || last; flip = !flip) {
    if (flip) curr->next = last, last = last->next;
    else curr->next = first, first = first->next;
    curr = curr->next;
  }

  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "zip_list.cc", "zip_list.tsv",
                         &ZippingLinkedList, DefaultComparator{}, param_names);
}
