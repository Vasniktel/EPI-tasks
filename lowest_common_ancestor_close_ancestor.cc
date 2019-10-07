#include <memory>
#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  std::unordered_set<BinaryTreeNode<int>*> nodes;
  
  auto a = node0.get(), b = node1.get();
  for (bool flip = false; a && b; flip = !flip) {
    auto*& node = flip ? a : b;
    if (nodes.find(node) != nodes.end()) return node;
    nodes.insert(node);
    node = node->parent;
  }
  
  while (a) {
    if (nodes.find(a) != nodes.end()) {
      return a;
    }
    a = a->parent;
  }
  
  while (b) {
    if (nodes.find(b) != nodes.end()) {
      return b;
    }
    b = b->parent;
  }
  
  assert(false);
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_close_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
