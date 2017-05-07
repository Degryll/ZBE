#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimpleDrawable.h"

namespace SimpleDrawable {

TEST(SimpleDrawable, Implementation) {
  zbe::SimpleDrawable sd(12, 28, 5040, 4096, 42);

  EXPECT_EQ(12,   sd.getX()) << "Initially, x is 12.";
  EXPECT_EQ(28,   sd.getY()) << "Initially, x is 28.";
  EXPECT_EQ(5040, sd.getW()) << "Initially, x is 5040.";
  EXPECT_EQ(4096, sd.getH()) << "Initially, x is 4096.";
  EXPECT_EQ(42,   sd.getGraphics()) << "Initially, x is 42.";

  sd.setX(13);

  EXPECT_EQ(13,   sd.getX()) << "X now is 13.";
  EXPECT_EQ(28,   sd.getY()) << "Y hasn't changed.";
  EXPECT_EQ(5040, sd.getW()) << "W hasn't changed.";
  EXPECT_EQ(4096, sd.getH()) << "H hasn't changed.";
  EXPECT_EQ(42,   sd.getGraphics()) << "Graphics hasn't changed.";

  sd.setY(29);

  EXPECT_EQ(13,   sd.getX()) << "X hasn't changed.";
  EXPECT_EQ(29,   sd.getY()) << "Y now is 29.";
  EXPECT_EQ(5040, sd.getW()) << "W hasn't changed.";
  EXPECT_EQ(4096, sd.getH()) << "H hasn't changed.";
  EXPECT_EQ(42,   sd.getGraphics()) << "Graphics hasn't changed.";

  sd.setW(10080);

  EXPECT_EQ(13,    sd.getX()) << "X hasn't changed.";
  EXPECT_EQ(29,    sd.getY()) << "Y hasn't changed.";
  EXPECT_EQ(10080, sd.getW()) << "W now is 10080.";
  EXPECT_EQ(4096,  sd.getH()) << "H hasn't changed.";
  EXPECT_EQ(42,    sd.getGraphics()) << "Graphics hasn't changed.";

  sd.setH(2048);

  EXPECT_EQ(13,    sd.getX()) << "X hasn't changed.";
  EXPECT_EQ(29,    sd.getY()) << "Y hasn't changed.";
  EXPECT_EQ(10080, sd.getW()) << "W hasn't changed.";
  EXPECT_EQ(2048,  sd.getH()) << "H now is 2018.";
  EXPECT_EQ(42,    sd.getGraphics()) << "Graphics hasn't changed.";

  sd.setGraphics(37);

  EXPECT_EQ(13,    sd.getX()) << "X hasn't changed.";
  EXPECT_EQ(29,    sd.getY()) << "Y hasn't changed.";
  EXPECT_EQ(10080, sd.getW()) << "W hasn't changed.";
  EXPECT_EQ(2048,  sd.getH()) << "H hasn't changed.";
  EXPECT_EQ(37,    sd.getGraphics()) << "Graphics now is 37.";
}

}  // namespace SimpleDampingTest
