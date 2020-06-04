#include <vector>
#include <unordered_map>
#include <list>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
using std::unordered_map;
using std::list;
using std::pair;

class LruCache {
  unordered_map<int, list<pair<int, int>>::iterator> keys_;
  list<pair<int, int>> values_;
  int capacity_;
 public:
  LruCache(size_t capacity)
  : capacity_(capacity)
  {}

  template <typename It>
  void update(It it) {
    auto data = *it->second;
    values_.erase(it->second);
    values_.push_front(data);
    it->second = values_.begin();
  }

  int Lookup(int isbn) {
    auto it = keys_.find(isbn);
    if (it == keys_.end()) return -1;
    update(it);
    return it->second->second;
  }
  void Insert(int isbn, int price) {
    auto it = keys_.find(isbn);
    if (it == keys_.end()) {
      if (keys_.size() == capacity_) {
        keys_.erase(values_.back().first);
        values_.pop_back();
      }

      values_.emplace_front(isbn, price);
      keys_[isbn] = values_.begin();
    } else update(it);
  }
  bool Erase(int isbn) {
    auto it = keys_.find(isbn);
    bool result = it != keys_.end();
    if (result) {
      values_.erase(it->second);
      keys_.erase(it);
    }

    return result;
  }
};
struct Op {
  std::string code;
  int arg1;
  int arg2;
};

template <>
struct SerializationTraits<Op> : UserSerTraits<Op, std::string, int, int> {};

void RunTest(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &RunTest,
                         DefaultComparator{}, param_names);
}
