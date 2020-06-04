#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
  if (square_matrix.empty()) return {};
  int size = square_matrix.size();
  vector<int> result;
  result.reserve(size * size);

  int top = 0, bottom = size - 1, left = 0, right = square_matrix[0].size() - 1;
  while (top <= bottom && left <= right) {
    for (int i = left; i <= right; ++i) {
      result.push_back(square_matrix[top][i]);
    }

    top++;

    for (int i = top; i <= bottom; ++i) {
      result.push_back(square_matrix[i][right]);
    }

    right--;

    for (int i = right; i >= left; --i) {
      result.push_back(square_matrix[bottom][i]);
    }

    bottom--;

    for (int i = bottom; i >= top; --i) {
      result.push_back(square_matrix[i][left]);
    }

    left++;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering_segments.cc",
                         "spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
                         DefaultComparator{}, param_names);
}
