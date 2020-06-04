#include <vector>
#include <complex>
#include "test_framework/generic_test.h"
using std::vector;
vector<double> GenerateFirstKABSqrt2(int k) {
  auto sqrt2 = sqrt(2);
  auto comp = [sqrt2](const auto& a, const auto& b) {
    return a.real() + a.imag() * sqrt2 < b.real() + b.imag() * sqrt2;
  };

  std::set<std::complex<int>, decltype(comp)> pq(comp);
  pq.emplace(0, 0);

  vector<double> result;
  result.reserve(k);

  while (result.size() != k) {
    auto top = *pq.begin();
    pq.erase(pq.begin());
    result.push_back(top.real() + top.imag() * sqrt2);
    pq.insert(top + 1);
    pq.insert(top + std::complex<int>(0, 1));
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "a_b_sqrt2.cc", "a_b_sqrt2.tsv",
                         &GenerateFirstKABSqrt2, DefaultComparator{},
                         param_names);
}
