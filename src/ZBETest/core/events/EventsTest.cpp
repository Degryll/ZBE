#include "gtest/gtest.h"

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/ReactObject.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

class R { // Reactor mock
};

class C : public zbe::Collisioner<R> {
  public:
    C(zbe::CollisionObject<R> * co):zbe::Collisioner<R>(co){};
    void react(zbe::CollisionData * collisionData, zbe::ReactObject<R> * reactObject) {};
};

class RO : public zbe::ReactObject<R> {
  public:
    void act(R* reactor){};
};

TEST(Event, TimeEvent) {
  zbe::TimeHandler* t = nullptr;
  zbe::TimeEvent e(1,100, t);
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  EXPECT_EQ(t, e.getHandler()) << "Must store the time handler";
}

TEST(Event, InputEvent) {
  zbe::InputEvent e(1,100, 7, 1.0);
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  EXPECT_EQ((uint64_t)7, e.getKey()) << "Must store the key id";
  EXPECT_EQ(1.0, e.getState()) << "Must store the key state";
}

TEST(Event, CollisionEvent) {
  zbe::StaticAABB2D<R>* coa = new zbe::StaticAABB2D<R>();
  C* c = new C(coa);
  RO * ro = new RO();
  zbe::Point2D p{4.0, 2.0};
  zbe::CollisionEvent2D<R> e(1,100, std::shared_ptr<zbe::Collisioner<R> >(c), p, std::shared_ptr<zbe::ReactObject<R> >(ro));
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  //EXPECT_EQ(c, e.getCollisioner()) << "Must store EntityA";
  EXPECT_EQ(p.x, e.getCollisionData().getPoint().x) << "Must store Point x coordinate";
  EXPECT_EQ(p.y, e.getCollisionData().getPoint().y) << "Must store Point y coordinate";
}
