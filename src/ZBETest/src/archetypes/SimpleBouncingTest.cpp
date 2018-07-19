#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimpleBouncing.h"

namespace SimpleBouncingTest {

TEST(SimpleBouncing, Implementation) {
  zbe::SimpleBouncing<2> sb2;

  EXPECT_FALSE(sb2.hasNormals()) << "Initially, hasn't any normal.";
  EXPECT_EQ(0.0, sb2.getNormalSum().x) << "Initially, the accumulated normals x position is zero.";
  EXPECT_EQ(0.0, sb2.getNormalSum().y) << "Initially, the accumulated normals y position is zero.";

  sb2.addNormal({3.0, 5.0});

  EXPECT_TRUE(sb2.hasNormals()) << "Added one normal.";
  EXPECT_EQ(3.0, sb2.getNormalSum().x) << "The accumulated normals x position is 3.0.";
  EXPECT_EQ(5.0, sb2.getNormalSum().y) << "The accumulated normals y position is 5.0.";

  sb2.addNormal({7.0, 11.0});

  EXPECT_TRUE(sb2.hasNormals()) << "Added another normal.";
  EXPECT_EQ(10.0, sb2.getNormalSum().x) << "The accumulated normals x position is 10.0.";
  EXPECT_EQ(16.0, sb2.getNormalSum().y) << "The accumulated normals y position is 16.0.";

  sb2.clearNormals();

  EXPECT_FALSE(sb2.hasNormals()) << "After clear, hasn't any normal.";
  EXPECT_EQ(0.0, sb2.getNormalSum().x) << "After clear, the accumulated normals x position is zero.";
  EXPECT_EQ(0.0, sb2.getNormalSum().y) << "After clear, the accumulated normals y position is zero.";

  zbe::SimpleBouncing<3> sb3;

  EXPECT_FALSE(sb3.hasNormals()) << "Initially, hasn't any normal.";
  EXPECT_EQ(0.0, sb3.getNormalSum().x) << "Initially, the accumulated normals x position is zero.";
  EXPECT_EQ(0.0, sb3.getNormalSum().y) << "Initially, the accumulated normals y position is zero.";
  EXPECT_EQ(0.0, sb3.getNormalSum().z) << "Initially, the accumulated normals z position is zero.";

  sb3.addNormal({3.0, 5.0, 7.0});

  EXPECT_TRUE(sb3.hasNormals()) << "Added one normal.";
  EXPECT_EQ(3.0, sb3.getNormalSum().x) << "The accumulated normals x position is 3.0.";
  EXPECT_EQ(5.0, sb3.getNormalSum().y) << "The accumulated normals y position is 5.0.";
  EXPECT_EQ(7.0, sb3.getNormalSum().z) << "The accumulated normals z position is 7.0.";

  sb3.addNormal({11.0, 13.0, 17.0});

  EXPECT_TRUE(sb3.hasNormals()) << "Added another normal.";
  EXPECT_EQ(14.0, sb3.getNormalSum().x) << "The accumulated normals x position is 14.0.";
  EXPECT_EQ(18.0, sb3.getNormalSum().y) << "The accumulated normals y position is 18.0.";
  EXPECT_EQ(24.0, sb3.getNormalSum().z) << "The accumulated normals z position is 24.0.";

  sb3.clearNormals();

  EXPECT_FALSE(sb3.hasNormals()) << "After clear, hasn't any normal.";
  EXPECT_EQ(0.0, sb3.getNormalSum().x) << "After clear, the accumulated normals x position is zero.";
  EXPECT_EQ(0.0, sb3.getNormalSum().y) << "After clear, the accumulated normals y position is zero.";
  EXPECT_EQ(0.0, sb3.getNormalSum().z) << "After clear, the accumulated normals z position is zero.";
}

}  // namespace SimpleBouncingTest
