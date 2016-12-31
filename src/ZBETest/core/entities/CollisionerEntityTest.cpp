#include "gtest/gtest.h"

#include "ZBE/core/entities/avatars/Collisioner.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"

class R { // Reactor mock
  public:
    virtual ~R() {};
};

class Coner : public zbe::Collisioner<R> {
  public:
    Coner(zbe::CollisionObject<R> * co):zbe::Collisioner<R>(co){};
    ~Coner(){};
    void react(zbe::CollisionData * collisionData, zbe::ReactObject<R> * reactObject) {};
};

TEST(Collisioner, Usage) {
  zbe::StaticAABB2D<R>* box1 = new zbe::StaticAABB2D<R>();
  zbe::StaticAABB2D<R>* box2 = new zbe::StaticAABB2D<R>();
  zbe::StaticAABB2D<R>* box3 = new zbe::StaticAABB2D<R>();

  Coner ce(box1); //

  EXPECT_EQ(box1,ce.getCollisionObject()) << "Same object.";
  EXPECT_NE(box2,ce.getCollisionObject()) << "Not same object.";
  EXPECT_NE(box3,ce.getCollisionObject()) << "Not same object.";

  ce.setCollisionObject(box2);

  EXPECT_NE(box1,ce.getCollisionObject()) << "Not same object.";
  EXPECT_EQ(box2,ce.getCollisionObject()) << "Same object.";
  EXPECT_NE(box3,ce.getCollisionObject()) << "Not same object.";

  ce.setCollisionObject(box3);

  EXPECT_NE(box1,ce.getCollisionObject()) << "Not same object.";
  EXPECT_NE(box2,ce.getCollisionObject()) << "Not same object.";
  EXPECT_EQ(box3,ce.getCollisionObject()) << "Same object.";
}

TEST(Collisioner, DISABLED_Actuators) {
  zbe::StaticAABB2D<R>* box = new zbe::StaticAABB2D<R>();
  Coner e(box);

//  e.addToActuatorsList(1, 3);
//  e.addToActuatorsList(2, 5);
//  e.addToActuatorsList(3, 7);
//  e.addToActuatorsList(4, 11);
//
//  EXPECT_EQ( 3u,e.getActuatorsList(1)) << "Add List Id for Actuator. - 1";
//  EXPECT_EQ( 5u,e.getActuatorsList(2)) << "Add List Id for Actuator. - 2";
//  EXPECT_EQ( 7u,e.getActuatorsList(3)) << "Add List Id for Actuator. - 3";
//  EXPECT_EQ(11u,e.getActuatorsList(4)) << "Add List Id for Actuator. - 4";
//
//  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
//  EXPECT_EQ(0u,e.getActuatorsList(42)) << "Access an invalid Actuator return list 0. - 4";
//  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing an invalid Actuator.";
//
//  zbe::SysError::clear();
//
//  e.removeFromActuatorsList(2);
//  e.addToActuatorsList(5, 13);
//
//  EXPECT_EQ( 3u,e.getActuatorsList(1)) << "Add List Id for Actuator. - 1";
//
//  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";
//  EXPECT_EQ( 0u,e.getActuatorsList(2)) << "Access removed Actuator. - 2";
//  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing a removed Actuator.";
//
//  zbe::SysError::clear();
//
//  EXPECT_EQ( 7u,e.getActuatorsList(3)) << "Add List Id for Actuator. - 3";
//  EXPECT_EQ(11u,e.getActuatorsList(4)) << "Add List Id for Actuator. - 4";
//  EXPECT_EQ(13u,e.getActuatorsList(5)) << "Add List Id for Actuator. - 5";
}
