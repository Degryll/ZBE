#include "gtest/gtest.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <time.h>

#include "ZBE/core/tools/math/math.h"
namespace math {

static const int ITERATIONS = 1;

TEST(math, DISABLED_MILITOZBETU) {
}

TEST(math, DISABLED_roundPrecision) {
}

TEST(math, div_Positive_Positive_Exact) {
  int64_t dividend = 6844761;
  int64_t divisor = 88893;
  int64_t result = 77 << zbe::PRECISION_DIGITS;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Positive_Positive_NoRound) {
  int64_t dividend = 105;//688831857; //10511
  int64_t divisor = 88893;
  int64_t result = 77;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Positive_Positive_Round) {
  int64_t dividend = 1052;
  int64_t divisor = 88893;
  int64_t result = 776;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Positive_Negative_Exact) {
  int64_t dividend = 6844761;
  int64_t divisor = -88893;
  int64_t result = -77 << zbe::PRECISION_DIGITS;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Positive_Negative_NoRound) {
  int64_t dividend = 105;
  int64_t divisor = -88893;
  int64_t result = -77;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Positive_Negative_Round) {
  int64_t dividend = 1052;
  int64_t divisor = -88893;
  int64_t result = -776 ;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Negative_Negative_Exact) {
  int64_t dividend = -6844761;
  int64_t divisor = -88893;
  int64_t result = 77 << zbe::PRECISION_DIGITS;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Negative_Negative_NoRound) {
  int64_t dividend = -105;
  int64_t divisor = -88893;
  int64_t result = 77;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Negative_Negative_Round) {
  int64_t dividend = -1052;
  int64_t divisor = -88893;
  int64_t result = 776;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Negative_Positive_Exact) {
  int64_t dividend = -6844761;
  int64_t divisor = 88893;
  int64_t result = -77 << zbe::PRECISION_DIGITS;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Negative_Positive_NoRound) {
  int64_t dividend = -105;
  int64_t divisor = 88893;
  int64_t result = -77;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

TEST(math, div_Negative_Positive_Round) {
  int64_t dividend = -1052;
  int64_t divisor = 88893;
  int64_t result = -776 ;
  EXPECT_EQ(result, zbe::div(dividend, divisor));
}

//*************Multiplication*************//

TEST(math, mult_Positive_Positive_Exact) {
  int64_t value1 = 98304;
  int64_t value2 = 196608;
  int64_t result = 294912;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Positive_Positive_NoRound) {
  int64_t value1 = 98306;
  int64_t value2 = 196605;
  int64_t result = 294913;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Positive_Positive_Round) {
  int64_t value1 = 98304;
  int64_t value2 = 196609;
  int64_t result = 294914;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Positive_Negative_Exact) {
  int64_t value1 = 98304;
  int64_t value2 = -196608;
  int64_t result = -294912;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Positive_Negative_NoRound) {
  int64_t value1 = 98306;
  int64_t value2 = -196605;
  int64_t result = -294913;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Positive_Negative_Round) {
  int64_t value1 = 98304;
  int64_t value2 = -196609;
  int64_t result = -294914;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Negative_Positive_Exact) {
  int64_t value1 = -98304;
  int64_t value2 = 196608;
  int64_t result = -294912;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Negative_Positive_NoRound) {
  int64_t value1 = -98306;
  int64_t value2 = 196605;
  int64_t result = -294913;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Negative_Positive_Round) {
  int64_t value1 = -98304;
  int64_t value2 = 196609;
  int64_t result = -294914;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Negative_Negative_Exact) {
  int64_t value1 = -98304;
  int64_t value2 = -196608;
  int64_t result = 294912;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Negative_Negative_NoRound) {
  int64_t value1 = -98306;
  int64_t value2 = -196605;
  int64_t result = 294913;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

TEST(math, mult_Negative_Negative_Round) {
  int64_t value1 = -98304;
  int64_t value2 = -196609;
  int64_t result = 294914;
  EXPECT_EQ(result, zbe::mult(value1, value2));
}

} // namespace math
