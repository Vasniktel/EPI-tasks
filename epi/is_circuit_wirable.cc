#include <stdexcept>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::vector;

struct GraphVertex {
  int d = 0;
  vector<GraphVertex*> edges;
};

bool recur(GraphVertex& v, int sign) {
  v.d = sign;

  for (auto* w : v.edges) {
    if (w->d == sign) return false;
    if (w->d == 0 && !recur(*w, -sign)) {
      return false;
    }
  }

  return true;
}

bool IsAnyPlacementFeasible(vector<GraphVertex>* graph) {
  for (auto& v : *graph) {
    if (v.d == 0) {
      if (!recur(v, 1)) {
        return false;
      }
    }
  }

  return true;
}
struct Edge {
  int from;
  int to;
};

template <>
struct SerializationTraits<Edge> : UserSerTraits<Edge, int, int> {};

bool IsAnyPlacementFeasibleWrapper(TimedExecutor& executor, int k,
                                   const vector<Edge>& edges) {
  vector<GraphVertex> graph;
  if (k <= 0) {
    throw std::runtime_error("Invalid k value");
  }
  graph.reserve(k);

  for (int i = 0; i < k; i++) {
    graph.push_back(GraphVertex{});
  }

  for (auto& e : edges) {
    if (e.from < 0 || e.from >= k || e.to < 0 || e.to >= k) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  return executor.Run([&] { return IsAnyPlacementFeasible(&graph); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "k", "edges"};
  return GenericTestMain(
      args, "is_circuit_wirable.cc", "is_circuit_wirable.tsv",
      &IsAnyPlacementFeasibleWrapper, DefaultComparator{}, param_names);
}
