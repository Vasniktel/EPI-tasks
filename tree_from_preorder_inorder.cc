#include <vector>
#include <unordered_map>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;
using ::std::move;
using ::std::stack;
using ::std::unordered_map;
using ::std::make_unique;

unique_ptr<BinaryTreeNode<int>> recur(
    const vector<int>& pre,
    const vector<int>& in,
    int prelo, int prehi,
    int inlo, int inhi,
    const unordered_map<int, int>& map) {
  if (prelo > prehi) return nullptr;
  int root = pre[prelo];
  int idx = map.at(root);
  int left_len = idx - inlo;
  auto left = recur(pre, in, prelo + 1, prelo + left_len, inlo, idx - 1, map);
  auto right = recur(pre, in, prelo + left_len + 1, prehi, idx + 1, inhi, map);
  return make_unique<BinaryTreeNode<int>>(root, move(left), move(right));
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  int n = preorder.size();
  unordered_map<int, int> map(n);
  for (int i = 0; i < n; ++i) map[inorder[i]] = i;
  return recur(preorder, inorder, 0, n - 1, 0, n - 1, map);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
