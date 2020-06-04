#include <stdexcept>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using std::deque;

void recur(vector<vector<char>>& board, int x, int y, deque<deque<bool>>& visited) {
  if (x < 0 || x >= board.size()) return;
  if (y < 0 || y >= board[0].size()) return;
  if (visited[x][y]) return;
  if (board[x][y] != 'W') return;
  
  visited[x][y] = true;
  
  recur(board, x - 1, y, visited);
  recur(board, x, y - 1, visited);
  recur(board, x + 1, y, visited);
  recur(board, x, y + 1, visited);
}

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
  auto& board = *board_ptr;
  int n = board.size(), m = board[0].size();
  deque<deque<bool>> visited(n, deque<bool>(m));
  
  for (int i = 0; i < m; ++i) {
    recur(board, 0, i, visited);
    recur(board, n - 1, i, visited);
  }
  
  for (int i = 1; i < n - 1; ++i) {
    recur(board, i, 0, visited);
    recur(board, i, m - 1, visited);
  }
  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!visited[i][j] && board[i][j] == 'W') {
        board[i][j] = 'B';
      }
    }
  }
}
vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
