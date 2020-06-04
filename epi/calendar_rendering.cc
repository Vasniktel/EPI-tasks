#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event {
  int start, finish;
};
int FindMaxSimultaneousEvents(const vector<Event>& A) {
  auto comp = [](const auto& a, const auto& b) {
    int val_a = a.second ? a.first.finish : a.first.start;
    int val_b = b.second ? b.first.finish : b.first.start;
    return std::tie(val_a, a.second) > std::tie(val_b, b.second);
  };

  std::priority_queue<std::pair<Event, bool>, vector<std::pair<Event, bool>>, decltype(comp)> pq(comp);

  for (const auto& event : A) pq.emplace(event, false);

  int result = 0, count = 0;
  while (!pq.empty()) {
    auto top = pq.top();
    pq.pop();

    if (top.second) count--;
    else {
      pq.emplace(top.first, true);
      count++;
      result = std::max(result, count);
    }
  }

  return result;
}
template <>
struct SerializationTraits<Event> : UserSerTraits<Event, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
