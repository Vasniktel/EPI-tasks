#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

string MajoritySearch(vector<string>::const_iterator stream_begin,
                      const vector<string>::const_iterator stream_end) {
  string result = *stream_begin;
  int count = 1;
  for (auto it = stream_begin + 1; it != stream_end; ++it) {
    if (*it == result) count++;
    else {
      count--;
      if (count == 0) {
        result = *(it + 1); // should exist
        count = 1;
      }
    }
  }
  
  return result;
}
string MajoritySearchWrapper(const vector<string>& stream) {
  return MajoritySearch(cbegin(stream), cend(stream));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "majority_element.cc", "majority_element.tsv",
                         &MajoritySearchWrapper, DefaultComparator{},
                         param_names);
}
