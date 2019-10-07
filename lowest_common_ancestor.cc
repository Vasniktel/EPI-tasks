#include <memory>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

enum MatchType {
  kFail       = 0b00,
  kPartLeft   = 0b01,
  kPartRight  = 0b10,
  kFull       = 0b11
};

::std::pair<MatchType, BinaryTreeNode<int>*> recur(
    BinaryTreeNode<int>* root,
    BinaryTreeNode<int>* node0,
    BinaryTreeNode<int>* node1) {
  if (!root) return {kFail, nullptr};
  if (root == node0 && root == node1) return {kFull, root};
  if (root == node0) {
    auto lmatch = recur(root->left.get(), node0, node1);
    if (lmatch.first == kPartRight) return {kFull, root};
    auto rmatch = recur(root->right.get(), node0, node1);
    if (rmatch.first == kPartRight) return {kFull, root};
    return {kPartLeft, nullptr};
  } else if (root == node1) {
    auto lmatch = recur(root->left.get(), node0, node1);
    if (lmatch.first == kPartLeft) return {kFull, root};
    auto rmatch = recur(root->right.get(), node0, node1);
    if (rmatch.first == kPartLeft) return {kFull, root};
    return {kPartRight, nullptr};
  } else {
    auto lmatch = recur(root->left.get(), node0, node1);
    if (lmatch.first == kFull) return lmatch;
    auto rmatch = recur(root->right.get(), node0, node1);
    if (rmatch.first == kFull) return rmatch;
    if ((lmatch.first == kPartLeft && rmatch.first == kPartRight) ||
        (lmatch.first == kPartRight && rmatch.first == kPartLeft))
      return {kFull, root};
    if (lmatch.first != kFail) return lmatch;
    if (rmatch.first != kFail) return rmatch;
    return {kFail, nullptr};
  }
}

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& tree,
                         const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  return recur(tree.get(), node0.get(), node1.get()).second;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
