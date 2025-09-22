#include "StringCalculator.h"
#include <gtest/gtest.h>
#include <string>

TEST(StringCalculatorTest, EmptyStringReturnsZero) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add(""), 0);
}

TEST(StringCalculatorTest, SingleNumber) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("5"), 5);
}

TEST(StringCalculatorTest, TwoNumbers) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1,2"), 3);
}

TEST(StringCalculatorTest, MultipleNumbers) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1,2,3,4"), 10);
}

TEST(StringCalculatorTest, NewlineDelimiter) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1\n2,3"), 6);
}

TEST(StringCalculatorTest, CustomDelimiter) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//;\n1;2"), 3);
}

TEST(StringCalculatorTest, NumbersGreaterThan1000Ignored) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("2,1001"), 2);
}

TEST(StringCalculatorTest, MultiCharDelimiter) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//[***]\n1***2***3"), 6);
}

TEST(StringCalculatorTest, NegativeThrowsException) {
  StringCalculator calc;
  EXPECT_THROW(calc.Add("1,-2,3"), std::invalid_argument);
}

TEST(StringCalculatorTest, MultipleNegativesInMessage) {
  StringCalculator calc;
  try {
    calc.Add("-1,-5,2");
    FAIL() << "Expected exception";
  } catch (const std::invalid_argument& ex) {
    std::string msg = ex.what();
    EXPECT_NE(msg.find("-1"), std::string::npos);
    EXPECT_NE(msg.find("-5"), std::string::npos);
  }
}
