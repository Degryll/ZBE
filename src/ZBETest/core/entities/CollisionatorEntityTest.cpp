#include "gtest/gtest.h"
TEST(DISABLED_Collisionator, Collisionables) {}
//#include "ZBE/core/entities/avatars/Collisionator.h"
//#include "ZBE/core/tools/math/collisions/ReactObject.h"
//#include "ZBE/core/tools/math/collisions/CollisionObject.h"
//#include "ZBE/core/tools/math/collisions/CollisionData.h"
//#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"
//
//#include <cstdint>
//
//
//class R { // Reactor mock
//};
//
//class Cator : public zbe::Collisionator<R> {
//  public:
//    Cator(uint64_t listId) : id(listId) {}
//    ~Cator() {}
//
//    zbe::CollisionObject<R>* getCollisionObject() {return (nullptr);}
//    zbe::ReactObject<R>* getReactObject() {return (nullptr);}
//
//    void react(zbe::CollisionData*, zbe::ReactObject<R>*) {}
//
//    uint64_t getCollisionablesListId() {return (id);}
//
//  private:
//    uint64_t id;
//};
//
//TEST(Collisionator, Collisionables) {
//  Cator c(1);
//
//  uint64_t id = c.getCollisionablesListId();
//
//  EXPECT_EQ(1, id) << "Must save list";
//}
