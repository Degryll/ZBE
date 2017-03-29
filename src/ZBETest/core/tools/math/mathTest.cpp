#include "gtest/gtest.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <time.h>

#include "ZBE/core/tools/math/math.h"
namespace math {

static const int ITERATIONS = 1;

TEST(math, quantizeTime) {
  EXPECT_EQ( 4352, zbe::quantizeTime( 4352)) <<  "17.00 * 256 round to  17 * 256.";
  EXPECT_EQ( 4352, zbe::quantizeTime( 4416)) <<  "17.25 * 256 round to  17 * 256.";
  EXPECT_EQ( 4352, zbe::quantizeTime( 4544)) <<  "17.75 * 256 round to  17 * 256.";
  /* Negative times not supported */
  /*EXPECT_EQ(-4352, zbe::quantizeTime(-4352)) << "-17.00 * 256 round to -17 * 256.";
  EXPECT_EQ(-4352, zbe::quantizeTime(-4416)) << "-17.25 * 256 round to -17 * 256.";
  EXPECT_EQ(-4352, zbe::quantizeTime(-4544)) << "-17.75 * 256 round to -17 * 256.";*/
}

} // namespace math
