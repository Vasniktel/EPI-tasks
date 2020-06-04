#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  ::std::stack<BinaryTreeNode<int>*> s;
  vector<int> result;

  for (auto node = tree.get(); !s.empty() || node;) {
    if (node) {
      s.push(node);
      node = node->left.get();
    } else {
      node = s.top();
      s.pop();
      result.push_back(node->data);
      node = node->right.get();
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
