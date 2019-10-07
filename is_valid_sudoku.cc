#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.

int cubeidx(int i, int j) {
  int a = i < 3 ? 0 : (i < 6 ? 1 : 2);
  int b = j < 3 ? 0 : (j < 6 ? 1 : 2);
  return a * 3 + b;
}

bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  assert(partial_assignment.size() == 9);
  unsigned cubes[9] = {};
  unsigned rows[9] = {};
  unsigned cols[9] = {};

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (partial_assignment[i][j] == 0) continue;
      auto mask = 1u << static_cast<unsigned>(partial_assignment[i][j] - 1);
      if (rows[i] & mask) return false;
      if (cols[j] & mask) return false;
      if (cubes[cubeidx(i, j)] & mask) return false;
      rows[i] |= mask;
      cols[j] |= mask;
      cubes[cubeidx(i, j)] |= mask;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
