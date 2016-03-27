#include "gtest/gtest.h"

#include "ZBE/core/entities/CollisionableEntity.h"
#include "ZBE/core/system/SysError.h"

//Dummy Entity implementation. Just for test purposes.
class CollisionableEntityTest : public zbe::CollisionableEntity {
};

TEST(CollisionableEntity, Collisionables) {
  CollisionableEntityTest e;

  e.addToCollisionablesList(1, 3);
  e.addToCollisionablesList(2, 5);
  e.addToCollisionablesList(3, 7);
  e.addToCollisionablesList(4, 11);

  EXPECT_EQ((uint64_t) 3,e.getCollisionablesList(1)) << "Add List Id for Collisonable. - 1";
  EXPECT_EQ((uint64_t) 5,e.getCollisionablesList(2)) << "Add List Id for Collisonable. - 2";
  EXPECT_EQ((uint64_t) 7,e.getCollisionablesList(3)) << "Add List Id for Collisonable. - 3";
  EXPECT_EQ((uint64_t)11,e.getCollisionablesList(4)) << "Add List Id for Collisonable. - 4";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initialy no errors.";
  EXPECT_EQ((uint64_t)0,e.getCollisionablesList(42)) << "Access an invalid collisionable return list 0. - 4";
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing an invalid collisionable.";

  zbe::SysError::clear();

  e.removeFromCollisionablesList(2);
  e.addToCollisionablesList(5, 13);

  EXPECT_EQ((uint64_t) 3,e.getCollisionablesList(1)) << "Add List Id for Collisonable. - 1";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
  EXPECT_EQ((uint64_t) 0,e.getCollisionablesList(2)) << "Access removed collisionable. - 2";
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing a removed collisionable.";

  zbe::SysError::clear();

  EXPECT_EQ((uint64_t) 7,e.getCollisionablesList(3)) << "Add List Id for Collisonable. - 3";
  EXPECT_EQ((uint64_t)11,e.getCollisionablesList(4)) << "Add List Id for Collisonable. - 4";
  EXPECT_EQ((uint64_t)13,e.getCollisionablesList(5)) << "Add List Id for Collisonable. - 5";
}

TEST(CollisionableEntity, Actuators) {
  CollisionableEntityTest e;

  e.addToActuatorsList(1, 3);
  e.addToActuatorsList(2, 5);
  e.addToActuatorsList(3, 7);
  e.addToActuatorsList(4, 11);

  EXPECT_EQ((uint64_t) 3,e.getActuatorsList(1)) << "Add List Id for Actuator. - 1";
  EXPECT_EQ((uint64_t) 5,e.getActuatorsList(2)) << "Add List Id for Actuator. - 2";
  EXPECT_EQ((uint64_t) 7,e.getActuatorsList(3)) << "Add List Id for Actuator. - 3";
  EXPECT_EQ((uint64_t)11,e.getActuatorsList(4)) << "Add List Id for Actuator. - 4";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
  EXPECT_EQ((uint64_t)0,e.getActuatorsList(42)) << "Access an invalid Actuator return list 0. - 4";
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing an invalid Actuator.";

  zbe::SysError::clear();

  e.removeFromActuatorsList(2);
  e.addToActuatorsList(5, 13);

  EXPECT_EQ((uint64_t) 3,e.getActuatorsList(1)) << "Add List Id for Actuator. - 1";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
  EXPECT_EQ((uint64_t) 0,e.getActuatorsList(2)) << "Access removed Actuator. - 2";
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing a removed Actuator.";

  zbe::SysError::clear();

  EXPECT_EQ((uint64_t) 7,e.getActuatorsList(3)) << "Add List Id for Actuator. - 3";
  EXPECT_EQ((uint64_t)11,e.getActuatorsList(4)) << "Add List Id for Actuator. - 4";
  EXPECT_EQ((uint64_t)13,e.getActuatorsList(5)) << "Add List Id for Actuator. - 5";
}
