#include "gtest/gtest.h"

#include <cstdio>

#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputStatus.h"

TEST (InputBuffer, insert) {
  zbe::InputBuffer buf;

  zbe::InputStatus a(1,0.0,10);
  zbe::InputStatus b(2,0.0,20);
  zbe::InputStatus c(3,0.0,30);
  zbe::InputStatus d(4,0.0,30);
  zbe::InputStatus e(5,0.0,40);
  zbe::InputStatus f(6,0.0,50);

  buf.insert(a);
  buf.insert(b);
  buf.insert(c);
  buf.insert(d);
  buf.insert(e);
  buf.insert(f);

  std::vector<zbe::InputStatus> store;

  buf.getRange(25,35,store);

  EXPECT_EQ(2,store.size()) << "just status c & d stored";
  EXPECT_EQ(30,store.at(0).getTime()) << "c = 30";
  EXPECT_EQ(30,store.at(1).getTime()) << "d = 30";

  store.clear();

  buf.getRange(35,55,store);

  EXPECT_EQ(1,store.size()) << "just status e stored";
  EXPECT_EQ(40,store.at(0).getTime()) << "e = 40";

}





