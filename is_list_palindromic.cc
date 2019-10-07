#include "list_node.h"
#include "test_framework/generic_test.h"

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  if (!L || !L->next) return true;

  int n = 0;
  for (auto node = L; node; node = node->next) {
    n++;
  }

  auto mid = L;
  for (int i = !(n & 1u); i < n / 2; ++i) {
    mid = mid->next;
  }

  auto hi = mid->next;
  while (hi->next) {
    auto tmp = hi->next;
    hi->next = mid;
    mid = hi;
    hi = tmp;
  }

  hi->next = mid;
  auto lo = L;
  while (hi != lo && hi->next != lo) {
    if (lo->data != hi->data) return false;
    lo = lo->next;
    hi = hi->next;
  }

  return hi->data == lo->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
