#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using std::queue;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) return {};
  queue<BinaryTreeNode<int>*> curr({tree.get()});
  vector<vector<int>> result;

  while (!curr.empty()) {
    decltype(curr) next;
    result.emplace_back();

    while (!curr.empty()) {
      auto node = curr.front(); curr.pop();
      result.back().push_back(node->data);
      if (node->left)  next.push(node->left.get());
      if (node->right) next.push(node->right.get());
    }

    curr = ::std::move(next);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
