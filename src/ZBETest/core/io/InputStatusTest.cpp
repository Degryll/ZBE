#include "gtest/gtest.h"

#include <cstdio>

#include "ZBE/core/io/InputStatus.h"

TEST (InputStatus, InputStatus) {
  zbe::InputStatus a(1,0.0,10);
  zbe::InputStatus b(2,1.0,20);

  EXPECT_EQ(1, a.getId()) << "id must match";
  EXPECT_EQ(0.0, a.getStatus()) << "status must match";
  EXPECT_EQ(10, a.getTime()) << "time must match";
  EXPECT_EQ(2, b.getId()) << "id must match";
  EXPECT_EQ(1.0, b.getStatus()) << "status must match";
  EXPECT_EQ(20, b.getTime()) << "time must match";

}





