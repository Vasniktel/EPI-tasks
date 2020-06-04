#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;
using std::greater;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator& sequence_end) {
  priority_queue<int> left;
  priority_queue<int, vector<int>, greater<>> right;
  vector<double> result;

  for (auto it = sequence_begin; it != sequence_end; ++it) {
    if (!left.empty() && *it < left.top()) left.push(*it);
    else right.push(*it);

    int lsize = left.size();
    int rsize = right.size();
    if (lsize - rsize > 1) {
      right.push(left.top());
      left.pop();
    } else if (rsize - lsize > 1) {
      left.push(right.top());
      right.pop();
    }

    if (left.size() == right.size()) {
      result.push_back((left.top() + right.top()) / 2.0);
    } else if (left.size() > right.size()) {
      result.push_back(left.top());
    } else {
      result.push_back(right.top());
    }
  }

  return result;
}
vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
