#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimplePosition.h"

#include "ZBE/core/tools/math/Point.h"

namespace SimplePositionTest {

TEST(SimplePosition, Implementation) {
  zbe::SimplePosition<2> sm2;

  EXPECT_EQ(0.0, sm2.getPosition().x) << "Initially, the position in x direction is zero.";
  EXPECT_EQ(0.0, sm2.getPosition().y) << "Initially, the position in y direction is zero.";

  sm2.setPosition({3.0, 5.0});

  EXPECT_EQ(3.0, sm2.getPosition().x) << "The position in x direction is 3.0.";
  EXPECT_EQ(5.0, sm2.getPosition().y) << "The position in y direction is 5.0.";

  zbe::Point<2> p2({7.0, 11.0});
  sm2.setPosition(p2);

  EXPECT_EQ(7.0, sm2.getPosition().x) << "The position in x direction is 7.0.";
  EXPECT_EQ(11.0, sm2.getPosition().y) << "The position in y direction is 11.0.";

  zbe::SimplePosition<3> sm3;

  EXPECT_EQ(0.0, sm3.getPosition().x) << "Initially, the position in x direction is zero.";
  EXPECT_EQ(0.0, sm3.getPosition().y) << "Initially, the position in y direction is zero.";
  EXPECT_EQ(0.0, sm3.getPosition().z) << "Initially, the position in z direction is zero.";

  sm3.setPosition({3.0, 5.0, 7.0});

  EXPECT_EQ(3.0, sm3.getPosition().x) << "The position in x direction is 3.0.";
  EXPECT_EQ(5.0, sm3.getPosition().y) << "The position in y direction is 5.0.";
  EXPECT_EQ(7.0, sm3.getPosition().z) << "The position in z direction is 7.0.";

  zbe::Point<3> p3({11.0, 13.0, 17.0});
  sm3.setPosition(p3);

  EXPECT_EQ(11.0, sm3.getPosition().x) << "The position in x direction is 11.0.";
  EXPECT_EQ(13.0, sm3.getPosition().y) << "The position in y direction is 13.0.";
  EXPECT_EQ(17.0, sm3.getPosition().z) << "The position in z direction is 17.0.";
}

}  // namespace SimplePositionTest
