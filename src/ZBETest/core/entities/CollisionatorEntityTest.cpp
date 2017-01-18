#include "gtest/gtest.h"

#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/ReactObject.h"
#include "ZBE/core/tools/math/collisions/CollisionData.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"

#include <cstdint>

class R { // Reactor mock
};

class Cator : public zbe::Collisionator<R> {
  public:
    Cator(zbe::CollisionObject<R> * co, uint64_t listId):zbe::Collisionator<R>(co, listId){};
    ~Cator(){};
    void react(zbe::CollisionData*, zbe::ReactObject<R>*) {};
};

TEST(Collisionator, Collisionables) {
  zbe::StaticAABB2D<R>*  box = new zbe::StaticAABB2D<R>();
  Cator c(box, 1); //Collisionator

  uint64_t id = c.getCollisionablesListId();

  EXPECT_EQ(1, id) << "Must save list";
}
