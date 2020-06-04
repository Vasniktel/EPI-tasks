#include <stdexcept>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::vector;
using std::deque;

struct GraphVertex {
  mutable bool visited = false;
  mutable bool on_stack = false;
  vector<GraphVertex*> edges;
};

bool recur(const GraphVertex& s) {
  s.visited = true;
  s.on_stack = true;

  for (const auto* edge : s.edges) {
    if (edge->on_stack) return true;
    if (!edge->visited && recur(*edge)) {
      return true;
    }
  }

  s.on_stack = false;
  return false;
}

bool IsDeadlocked(vector<GraphVertex>* graph_ptr) {
  const auto& graph = *graph_ptr;
  return std::any_of(graph.begin(), graph.end(), [](const auto& vertex) {
    return !vertex.visited && recur(vertex);
  });
}
struct Edge {
  int from;
  int to;
};

template <>
struct SerializationTraits<Edge> : UserSerTraits<Edge, int, int> {};

bool HasCycleWrapper(TimedExecutor& executor, int num_nodes,
                     const vector<Edge>& edges) {
  vector<GraphVertex> graph;
  if (num_nodes <= 0) {
    throw std::runtime_error("Invalid num_nodes value");
  }
  graph.reserve(num_nodes);

  for (int i = 0; i < num_nodes; i++) {
    graph.push_back(GraphVertex{});
  }

  for (const Edge& e : edges) {
    if (e.from < 0 || e.from >= num_nodes || e.to < 0 || e.to >= num_nodes) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  return executor.Run([&] { return IsDeadlocked(&graph); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_nodes", "edges"};
  return GenericTestMain(args, "deadlock_detection.cc",
                         "deadlock_detection.tsv", &HasCycleWrapper,
                         DefaultComparator{}, param_names);
}
