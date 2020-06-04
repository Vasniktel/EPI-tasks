#include <deque>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;

void recur(vector<deque<bool>>& image, int x, int y, bool val, deque<deque<bool>>& visited) {
  if (x < 0 || x >= image.size()) return;
  if (y < 0 || y >= image[0].size()) return;
  if (visited[x][y]) return;
  if (image[x][y] != val) return;
  visited[x][y] = true;
  image[x][y] = !val;
  
  recur(image, x - 1, y, val, visited);
  recur(image, x, y - 1, val, visited);
  recur(image, x + 1, y, val, visited);
  recur(image, x, y + 1, val, visited);
}

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
  auto& image = *image_ptr;
  deque<deque<bool>> visited(image.size(), deque<bool>(image[0].size(), false));
  recur(image, x, y, image[x][y], visited);
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
