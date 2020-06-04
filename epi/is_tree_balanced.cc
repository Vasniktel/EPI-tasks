#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

::std::pair<bool, int> recur(const BinaryTreeNode<int>* root) {
  if (!root) return {true, 0};
  auto left = recur(root->left.get());
  auto right = recur(root->right.get());
  int height = ::std::max(left.second, right.second) + 1;
  bool balanced = left.first && right.first && abs(left.second - right.second) <= 1;
  return {balanced, height};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return recur(tree.get()).first;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
