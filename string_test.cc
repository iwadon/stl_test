#include <string>
#include <gtest/gtest.h>

TEST(StringTest, assign) {
  std::string s1("abcdefg");
  std::string s2;
  s2.assign(s1.begin(), s1.end());
  EXPECT_EQ(s1, s2);
  s2.assign(s1.begin(), s1.begin());
  EXPECT_EQ("", s2);
  s2.assign(s1.end(), s1.end());
  EXPECT_EQ("", s2);
  EXPECT_THROW(s2.assign(s1.end(), s1.begin()), std::length_error);
}
