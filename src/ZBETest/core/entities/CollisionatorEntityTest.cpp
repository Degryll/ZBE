#include "gtest/gtest.h"

#include "ZBE/core/entities/CollisionatorEntity.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"

TEST(CollisionatorEntity, Collisionables) {
  zbe::StaticAABB2D box;
  zbe::CollisionatorEntity e(&box);

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

TEST(CollisionatorEntity, Actuators) {
  zbe::StaticAABB2D box;
  zbe::CollisionatorEntity e(&box);

  e.addToActuatorsList(1, 3);
  e.addToActuatorsList(2, 5);
  e.addToActuatorsList(3, 7);
  e.addToActuatorsList(4, 11);

  EXPECT_EQ( 3u,e.getActuatorsList(1)) << "Add List Id for Actuator. - 1";
  EXPECT_EQ( 5u,e.getActuatorsList(2)) << "Add List Id for Actuator. - 2";
  EXPECT_EQ( 7u,e.getActuatorsList(3)) << "Add List Id for Actuator. - 3";
  EXPECT_EQ(11u,e.getActuatorsList(4)) << "Add List Id for Actuator. - 4";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
  EXPECT_EQ(0u,e.getActuatorsList(42)) << "Access an invalid Actuator return list 0. - 4";
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing an invalid Actuator.";

  zbe::SysError::clear();

  e.removeFromActuatorsList(2);
  e.addToActuatorsList(5, 13);

  EXPECT_EQ( 3u,e.getActuatorsList(1)) << "Add List Id for Actuator. - 1";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
  EXPECT_EQ( 0u,e.getActuatorsList(2)) << "Access removed Actuator. - 2";
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing a removed Actuator.";

  zbe::SysError::clear();

  EXPECT_EQ( 7u,e.getActuatorsList(3)) << "Add List Id for Actuator. - 3";
  EXPECT_EQ(11u,e.getActuatorsList(4)) << "Add List Id for Actuator. - 4";
  EXPECT_EQ(13u,e.getActuatorsList(5)) << "Add List Id for Actuator. - 5";
}
