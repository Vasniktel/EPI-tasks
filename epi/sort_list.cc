#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> recur(shared_ptr<ListNode<int>> list, int len) {
  if (len == 0) return nullptr;
  if (len == 1) {
    list->next = nullptr;
    return list;
  }

  auto middle = list;
  for (int i = 0; i < len / 2; ++i) {
    middle = middle->next;
  }

  auto l = recur(list, len / 2);
  auto r = recur(middle, len / 2 + (len & 1));

  auto lo = l, hi = r, head = make_shared<ListNode<int>>(), curr = head;
  while (lo || hi) {
    shared_ptr<ListNode<int>>* node;

    if      (!lo) node = &hi;
    else if (!hi) node = &lo;
    else if (hi->data < lo->data) node = &hi;
    else node = &lo;

    curr->next = *node;
    curr = curr->next;
    *node = (*node)->next;
  }

  curr->next = nullptr;
  return head->next;
}

shared_ptr<ListNode<int>> StableSortList(shared_ptr<ListNode<int>> L) {
  int n = 0;
  for (auto node = L; node; node = node->next) n++;
  return recur(L, n);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "sort_list.cc", "sort_list.tsv", &StableSortList,
                         DefaultComparator{}, param_names);
}
