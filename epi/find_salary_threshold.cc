#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

double FindSalaryCap(int target_payroll, vector<int> current_salaries) {
  std::sort(current_salaries.begin(), current_salaries.end());

  for (int i = 0, sum = 0, n = current_salaries.size(); i < n; ++i) {
    int cap = sum + (n - i) * current_salaries[i];
    if (cap >= target_payroll) {
      return static_cast<double>(target_payroll - sum) / (n - i);
    }

    sum += current_salaries[i];
  }

  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"target_payroll", "current_salaries"};
  return GenericTestMain(args, "find_salary_threshold.cc",
                         "find_salary_threshold.tsv", &FindSalaryCap,
                         DefaultComparator{}, param_names);
}
