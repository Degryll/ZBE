#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimpleMobile.h"

#include "ZBE/core/tools/math/Vector.h"

namespace SimpleMobileTest {

TEST(SimpleMobile, Implementation) {
  zbe::SimpleMobile<2> sm2;

  EXPECT_EQ(0.0, sm2.getVelocity().x) << "Initially, the velocity in x direction is zero.";
  EXPECT_EQ(0.0, sm2.getVelocity().y) << "Initially, the velocity in y direction is zero.";

  sm2.setVelocity({3.0, 5.0});

  EXPECT_EQ(3.0, sm2.getVelocity().x) << "The velocity in x direction is 3.0.";
  EXPECT_EQ(5.0, sm2.getVelocity().y) << "The velocity in y direction is 5.0.";

  zbe::Vector<2> v2({7.0, 11.0});
  sm2.setVelocity(v2);

  EXPECT_EQ(7.0, sm2.getVelocity().x) << "The velocity in x direction is 7.0.";
  EXPECT_EQ(11.0, sm2.getVelocity().y) << "The velocity in y direction is 11.0.";

  zbe::SimpleMobile<3> sm3;

  EXPECT_EQ(0.0, sm3.getVelocity().x) << "Initially, the velocity in x direction is zero.";
  EXPECT_EQ(0.0, sm3.getVelocity().y) << "Initially, the velocity in y direction is zero.";
  EXPECT_EQ(0.0, sm3.getVelocity().z) << "Initially, the velocity in z direction is zero.";

  sm3.setVelocity({3.0, 5.0, 7.0});

  EXPECT_EQ(3.0, sm3.getVelocity().x) << "The velocity in x direction is 3.0.";
  EXPECT_EQ(5.0, sm3.getVelocity().y) << "The velocity in y direction is 5.0.";
  EXPECT_EQ(7.0, sm3.getVelocity().z) << "The velocity in z direction is 7.0.";

  zbe::Vector<3> v3({11.0, 13.0, 17.0});
  sm3.setVelocity(v3);

  EXPECT_EQ(11.0, sm3.getVelocity().x) << "The velocity in x direction is 11.0.";
  EXPECT_EQ(13.0, sm3.getVelocity().y) << "The velocity in y direction is 13.0.";
  EXPECT_EQ(17.0, sm3.getVelocity().z) << "The velocity in z direction is 17.0.";
}

}  // namespace SimpleMobileTest
