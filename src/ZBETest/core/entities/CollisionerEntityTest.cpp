#include "gtest/gtest.h"

#include "ZBE/core/entities/CollisionerEntity.h"

#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"

TEST(CollisionerEntity, Usage) {
  zbe::StaticAABB2D box1;
  zbe::StaticAABB2D box2;
  zbe::StaticAABB2D box3;

  zbe::CollisionerEntity ce(&box1);

  EXPECT_EQ(&box1,ce.getCollisionObject()) << "Same object.";
  EXPECT_NE(&box2,ce.getCollisionObject()) << "Not same object.";
  EXPECT_NE(&box3,ce.getCollisionObject()) << "Not same object.";

  ce.setCollisionObject(&box2);

  EXPECT_NE(&box1,ce.getCollisionObject()) << "Not same object.";
  EXPECT_EQ(&box2,ce.getCollisionObject()) << "Same object.";
  EXPECT_NE(&box3,ce.getCollisionObject()) << "Not same object.";

  ce.setCollisionObject(&box3);

  EXPECT_NE(&box1,ce.getCollisionObject()) << "Not same object.";
  EXPECT_NE(&box2,ce.getCollisionObject()) << "Not same object.";
  EXPECT_EQ(&box3,ce.getCollisionObject()) << "Same object.";
}
