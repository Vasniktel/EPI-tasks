#include <bits/stdc++.h>
#include "gtest/gtest.h"

using namespace std;

bool run(std::string s) {
  sort(s.begin(), s.end());

  for (int i = 1, n = s.size(); i < n; ++i) {
    if (s[i] == s[i - 1]) {
      return false;
    }
  }

  return true;
}

TEST(UniqueCharacters, Basic) {
  ASSERT_TRUE(run("abc"));
  ASSERT_FALSE(run("aab"));
  ASSERT_TRUE(run(""));
}
