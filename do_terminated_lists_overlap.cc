#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  int size1 = 0;
  for (auto node = l0; node; node = node->next) {
    size1++;
  }
  
  int size2 = 0;
  for (auto node = l1; node; node = node->next) {
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
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
