#include <string>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using ::std::move;
using ::std::stack;
using ::std::pair;
using std::make_unique;

void Assign(pair<int, unique_ptr<BinaryTreeNode<int>>>& p, unique_ptr<BinaryTreeNode<int>>&& child) {
  (p.first ? p.second->right : p.second->left) = move(child);
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
    const vector<int*>& preorder) {
  stack<pair<int, unique_ptr<BinaryTreeNode<int>>>> s;

  for (int* val : preorder) {
    if (!val) {
      if (s.empty()) return nullptr;
      s.top().first++;
      while (s.top().first == 2) {
        auto node = move(s.top().second);
        s.pop();
        if (s.empty()) return node;
        Assign(s.top(), move(node));
        s.top().first++;
      }
    } else {
      s.emplace(0, make_unique<BinaryTreeNode<int>>(*val));
    }
  }

  return move(s.top().second);
}
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(preorder.size());
  for (auto& s : preorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "preorder"};
  return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                         "tree_from_preorder_with_null.tsv",
                         &ReconstructPreorderWrapper, DefaultComparator{},
                         param_names);
}
