#include <vector>
#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval {
  int left, right;
};

bool intersects(const Interval& a, const Interval& b) {
  return !(a.right < b.left || a.left > b.right);
}

vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals,
                             Interval new_interval) {
  vector<Interval> result;

  int i = 0, n = disjoint_intervals.size();

  while (i < n && new_interval.left > disjoint_intervals[i].right) {
    result.push_back(disjoint_intervals[i]);
    i++;
  }

  result.push_back(new_interval);

  while (i < n && intersects(result.back(), disjoint_intervals[i])) {
    result.back().left = std::min(result.back().left, disjoint_intervals[i].left);
    result.back().right = std::max(result.back().right, disjoint_intervals[i].right);
    i++;
  }

  result.insert(result.end(), disjoint_intervals.begin() + i, disjoint_intervals.end());

  return result;
}
template <>
struct SerializationTraits<Interval> : UserSerTraits<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};

bool operator==(const Interval& a, const Interval& b) {
  return a.left == b.left && a.right == b.right;
}

std::ostream& operator<<(std::ostream& out, const Interval& i) {
  return PrintTo(out, std::make_tuple(i.left, i.right));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"disjoint_intervals", "new_interval"};
  return GenericTestMain(args, "interval_add.cc", "interval_add.tsv",
                         &AddInterval, DefaultComparator{}, param_names);
}
