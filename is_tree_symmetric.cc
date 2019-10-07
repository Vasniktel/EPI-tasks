#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool recur(const BinaryTreeNode<int>* left, const BinaryTreeNode<int>* right) {
  if (!left && !right) return true;
  if (!left || !right) return false;
  if (left->data != right->data) return false;
  return recur(left->left.get(), right->right.get()) && recur(left->right.get(), right->left.get());
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) return true;
  return recur(tree->left.get(), tree->right.get());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
