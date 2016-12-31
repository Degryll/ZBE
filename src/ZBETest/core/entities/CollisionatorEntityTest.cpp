#include "gtest/gtest.h"

#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/ReactObject.h"
#include "ZBE/core/tools/math/collisions/CollisionData.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"

class R { // Reactor mock
};

class Cator : public zbe::Collisionator<R> {
  public:
    Cator(zbe::CollisionObject<R> * co):zbe::Collisionator<R>(co){};
    ~Cator(){};
    void react(zbe::CollisionData * collisionData, zbe::ReactObject<R> * reactObject) {};
};

TEST(Collisionator, Collisionables) {
  zbe::StaticAABB2D<R>*  box = new zbe::StaticAABB2D<R>();
  Cator c(box); //Collisionator

  c.addToCollisionablesLists(1);
  c.addToCollisionablesLists(2);
  c.addToCollisionablesLists(3);
  c.addToCollisionablesLists(4);

  const std::forward_list<uint64_t>& cl = c.getCollisionablesLists();
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

  c.removeFromCollisionablesLists(2);
  c.addToCollisionablesLists(5);
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
