#include <string>
#include <utility>
#include <unordered_map>
#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

class ClientsCreditsInfo {
  std::unordered_map<string, int> a;
  std::map<int, std::unordered_set<string>> b;
  int offset = 0;
 public:
  void Insert(const string& client_id, int c) {
    a[client_id] = c - offset;
    b[c - offset].insert(client_id);
  }
  bool Remove(const string& client_id) {
    auto it = a.find(client_id);
    if (it == a.end()) return false;
    b[it->second].erase(client_id);
    a.erase(it);
    return true;
  }
  int Lookup(const string& client_id) const {
    auto it = a.find(client_id);
    return it == a.end() ? -1 : it->second + offset;
  }
  void AddAll(int C) {
    offset += C;
  }
  string Max() const {
    return *b.rbegin()->second.begin();
  }
};
struct Operation {
  std::string op;
  std::string s_arg;
  int i_arg;
};

std::ostream& operator<<(std::ostream& out, const Operation& op) {
  return out << FmtStr("{}({}, {})", op.op, op.s_arg, op.i_arg);
}

template <>
struct SerializationTraits<Operation>
    : UserSerTraits<Operation, std::string, std::string, int> {};

void ClientsCreditsInfoTester(const std::vector<Operation>& ops) {
  ClientsCreditsInfo cr;
  int op_idx = 0;
  for (auto& op : ops) {
    if (op.op == "ClientsCreditsInfo") {
      continue;
    } else if (op.op == "remove") {
      bool result = cr.Remove(op.s_arg);
      if (result != op.i_arg) {
        throw TestFailure()
            .WithProperty(PropertyName::STATE, cr)
            .WithProperty(PropertyName::COMMAND, op)
            .WithMismatchInfo(op_idx, op.i_arg, result);
      }
    } else if (op.op == "max") {
      auto result = cr.Max();
      if (result != op.s_arg) {
        throw TestFailure()
            .WithProperty(PropertyName::STATE, cr)
            .WithProperty(PropertyName::COMMAND, op)
            .WithMismatchInfo(op_idx, op.i_arg, result);
      }
    } else if (op.op == "insert") {
      cr.Insert(op.s_arg, op.i_arg);
    } else if (op.op == "add_all") {
      cr.AddAll(op.i_arg);
    } else if (op.op == "lookup") {
      auto result = cr.Lookup(op.s_arg);
      if (result != op.i_arg) {
        throw TestFailure()
            .WithProperty(PropertyName::STATE, cr)
            .WithProperty(PropertyName::COMMAND, op)
            .WithMismatchInfo(op_idx, op.i_arg, result);
        ;
      }
    }
    op_idx++;
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "adding_credits.cc", "adding_credits.tsv",
                         &ClientsCreditsInfoTester, DefaultComparator{},
                         param_names);
}
