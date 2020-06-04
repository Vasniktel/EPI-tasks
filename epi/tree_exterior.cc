#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

void recur(const unique_ptr<BinaryTreeNode<int>>* node, vector<const unique_ptr<BinaryTreeNode<int>>*>& buff) {
  if (!(*node)->left && !(*node)->right) {
    buff.push_back(node);
    return;
  }

  if ((*node)->left) recur(&(*node)->left, buff);
  if ((*node)->right) recur(&(*node)->right, buff);
}

// NOTE: test cases seem to be incorrect
vector<const unique_ptr<BinaryTreeNode<int>>*> ExteriorBinaryTree(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) return {};

  vector<const unique_ptr<BinaryTreeNode<int>>*> result;

  auto node = &tree;
  for (; (*node)->left; node = &(*node)->left) {
    result.push_back(node);
  }

  if ((*node)->right) result.push_back(node);

  recur(&tree, result);

  auto size = result.size();
  node = &tree;
  for (; (*node)->right; node = &(*node)->right) {
    result.push_back(node);
  }

  if ((*node)->left) result.push_back(node);
  ::std::reverse(result.begin() + size, result.end());
  result.pop_back();
  return result;
}
vector<int> CreateOutputVector(
    const vector<const unique_ptr<BinaryTreeNode<int>>*>& L) {
  if (std::find(std::begin(L), std::end(L), nullptr) != std::end(L)) {
    throw TestFailure("Resulting list contains nullptr");
  }
  std::vector<int> output;
  for (const auto* l : L) {
    output.push_back((*l)->data);
  }
  return output;
}

vector<int> ExteriorBinaryTreeWrapper(
    TimedExecutor& executor, const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto result = executor.Run([&] { return ExteriorBinaryTree(tree); });

  return CreateOutputVector(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_exterior.cc", "tree_exterior.tsv",
                         &ExteriorBinaryTreeWrapper, DefaultComparator{},
                         param_names);
}
