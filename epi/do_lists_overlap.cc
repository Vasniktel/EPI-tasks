#include <set>
#include <stdexcept>
#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1,
    shared_ptr<ListNode<int>> last) {
  int size1 = 0;
  for (auto node = l0; node != last; node = node->next) {
    size1++;
  }

  int size2 = 0;
  for (auto node = l1; node != last; node = node->next) {
    size2++;
  }

  auto small = size1 < size2 ? l0 : l1;
  auto big = size1 < size2 ? l1 : l0;
  int small_size = ::std::min(size1, size2);
  int big_size = ::std::max(size1, size2);

  for (int i = 0; i < big_size - small_size; ++i) {
    big = big->next;
  }

  for (int i = 0; i < small_size; ++i) {
    if (big == small) return big;
    big = big->next;
    small = small->next;
  }

  return nullptr;
}

shared_ptr<ListNode<int>> getCycle(shared_ptr<ListNode<int>> list) {
  if (!list) return nullptr;
  auto slow = list, fast = list->next;

  for (auto flip = false; fast && fast != slow; flip = !flip) {
    fast = fast->next;
    if (flip) slow = slow->next;
  }

  return fast;
}

shared_ptr<ListNode<int>> OverlappingLists(shared_ptr<ListNode<int>> l0,
                                           shared_ptr<ListNode<int>> l1) {
  if (!l0 || !l1) return nullptr;
  auto cycle1 = getCycle(l0);
  auto cycle2 = getCycle(l1);

  if (cycle1 && cycle2) {
    auto node = cycle1->next;
    do {
      node = node->next;
    } while (node != cycle1 && node != cycle2);

    if (node != cycle2) return nullptr;

    return OverlappingNoCycleLists(l0, l1, cycle1);
  } else if (!cycle1 && !cycle2) {
    return OverlappingNoCycleLists(l0, l1, nullptr);
  }

  return nullptr;
}
void OverlappingListsWrapper(TimedExecutor& executor,
                             shared_ptr<ListNode<int>> l0,
                             shared_ptr<ListNode<int>> l1,
                             shared_ptr<ListNode<int>> common, int cycle0,
                             int cycle1) {
  if (common) {
    if (!l0) {
      l0 = common;
    } else {
      auto it = l0;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }

    if (!l1) {
      l1 = common;
    } else {
      auto it = l1;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }
  }

  if (cycle0 != -1 && l0) {
    auto last = l0;
    while (last->next) {
      last = last->next;
    }
    auto it = l0;
    while (cycle0-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  if (cycle1 != -1 && l1) {
    auto last = l1;
    while (last->next) {
      last = last->next;
    }
    auto it = l1;
    while (cycle1-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  std::set<shared_ptr<ListNode<int>>> common_nodes;
  auto it = common;
  while (it && common_nodes.count(it) == 0) {
    common_nodes.insert(it);
    it = it->next;
  }

  auto result = executor.Run([&] { return OverlappingLists(l0, l1); });

  if (!((common_nodes.empty() && result == nullptr) ||
        common_nodes.count(result) > 0)) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0",     "l1",
                                       "common",   "cycle0", "cycle1"};
  return GenericTestMain(args, "do_lists_overlap.cc", "do_lists_overlap.tsv",
                         &OverlappingListsWrapper, DefaultComparator{},
                         param_names);
}
