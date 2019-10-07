#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
class Queue {
  ::std::vector<int> data_;
  int lo, hi, size;
 public:
  Queue(size_t capacity)
  : data_(capacity),
    lo(0),
    hi(0),
    size(0)
  {}

  void Enqueue(int x) {
    if (Size() == Capacity()) {
      Resize(Size() * 2);
    }

    data_[hi] = x;
    hi = (hi + 1) % Capacity();
    size++;
  }
  int Dequeue() {
    if (Size() == 0) {
      throw ::std::length_error{""};
    }

    int result = data_[lo];
    lo = (lo + 1) % Capacity();
    size--;
    return result;
  }
  int Size() const {
    return size;
  }

  void Resize(size_t cap) {
    assert(cap > Capacity());
    ::std::vector<int> new_data(cap);

    int n = Size();
    for (int i = 0; i < n; ++i) {
      new_data[i] = data_[(lo + i) % n];
    }

    data_ = ::std::move(new_data);
    lo = 0;
    hi = n;
  }

  int Capacity() const {
    return data_.size();
  }
};
struct QueueOp {
  enum { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = kConstruct;
    } else if (op_string == "dequeue") {
      op = kDequeue;
    } else if (op_string == "enqueue") {
      op = kEnqueue;
    } else if (op_string == "size") {
      op = kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case kEnqueue:
        q.Enqueue(argument);
        break;
      case kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

template <>
struct SerializationTraits<QueueOp> : UserSerTraits<QueueOp, std::string, int> {
};

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
