#include "gtest/gtest.h"

#include "ZBE/core/entities/avatars/Collisionator.h"

#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"

TEST(Collisionator, Collisionables) {
  zbe::StaticAABB2D box;
  zbe::Collisionator e(&box);

  e.addToCollisionablesLists(1);
  e.addToCollisionablesLists(2);
  e.addToCollisionablesLists(3);
  e.addToCollisionablesLists(4);

  const std::forward_list<uint64_t>& cl = e.getCollisionablesLists();
  auto it = cl.begin();

  EXPECT_EQ(4,*it) << "Add List Id for Collisonable. - 4";
  ++it;
  EXPECT_EQ(3,*it) << "Add List Id for Collisonable. - 3";
  ++it;
  EXPECT_EQ(2,*it) << "Add List Id for Collisonable. - 2";
  ++it;
  EXPECT_EQ(1,*it) << "Add List Id for Collisonable. - 1";
  ++it;
  EXPECT_EQ(cl.end(),it) << "End list.";

  e.removeFromCollisionablesLists(2);
  e.addToCollisionablesLists(5);
  it = cl.begin();

  EXPECT_EQ(5,*it) << "Add List Id for Collisonable. - 5";
  ++it;
  EXPECT_EQ(4,*it) << "Sill in List Id for Collisonable. - 4";
  ++it;
  EXPECT_EQ(3,*it) << "Sill in List Id for Collisonable. - 3";
  ++it;
  EXPECT_EQ(1,*it) << "Sill in List Id for Collisonable. - 1";
  ++it;
  EXPECT_EQ(cl.end(),it) << "End list.";
}
