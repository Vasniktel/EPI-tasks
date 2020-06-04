#include "test_framework/generic_test.h"
unsigned long long Add(unsigned long long x, unsigned long long y) {
  auto k = 1ull, sum = 0ull, carry = 0ull, temp_x = x, temp_y = y;

  while (temp_x || temp_y) {
    auto xk = x & k, yk = y & k;
    auto carryout = (xk & yk) | (xk & carry) | (yk & carry);
    sum |= (xk ^ yk ^ carry);
    carry = carryout << 1u;
    temp_x >>= 1u;
    temp_y >>= 1u;
    k <<= 1u;
  }

  return sum | carry;
}

unsigned long long Multiply(unsigned long long x, unsigned long long y) {
  auto result = 0ull;

  while (x) {
    if (x & 1u) result = Add(result, y);
    x >>= 1u;
    y <<= 1u;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  std::cout << Multiply(57536, 2187);
  return GenericTestMain(args, "primitive_multiply.cc",
                         "primitive_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
