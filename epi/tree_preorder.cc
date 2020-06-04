#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) return {};
  ::std::stack<BinaryTreeNode<int>*> s({tree.get()});
  vector<int> result;
  
  while (!s.empty()) {
    auto node = s.top();
    s.pop();
    
    result.push_back(node->data);
    if (node->right) s.push(node->right.get());
    if (node->left) s.push(node->left.get());
  }
  
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
