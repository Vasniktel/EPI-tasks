#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

void recur(const BinaryTreeNode<int>* node, unsigned& buff, unsigned& ans) {
  if (!node) return;

  buff = (buff << 1u) | static_cast<unsigned>(node->data);

  if (!node->left && !node->right) ans += buff;
  if (node->left)  recur(node->left.get(), buff, ans);
  if (node->right) recur(node->right.get(), buff, ans);

  buff >>= 1u;
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto buff = 0u, result = 0u;
  recur(tree.get(), buff, result);
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
