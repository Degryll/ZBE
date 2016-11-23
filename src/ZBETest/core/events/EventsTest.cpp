#include "gtest/gtest.h"

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventDispatcher.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"


TEST(Event, TimeEvent) {
  zbe::TimeEvent e(1,100, 2);
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  EXPECT_EQ((uint64_t)2, e.getTimerId()) << "Must store the timer id";
}

TEST(Event, InputEvent) {
  zbe::InputEvent e(1,100, 7, 1.0);
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  EXPECT_EQ((uint64_t)7, e.getKey()) << "Must store the key id";
  EXPECT_EQ(1.0, e.getState()) << "Must store the key state";
}

TEST(Event, CollisionEvent) {
  zbe::StaticAABB2D* coa = new zbe::StaticAABB2D();
  zbe::Collisioner* a = new zbe::Collisioner(coa);
  zbe::Point2D p{4.0, 2.0};
  zbe::CollisionEvent2D e(1,100, a, p);
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  EXPECT_EQ(a, e.getEntity()) << "Must store EntityA";
  EXPECT_EQ(p.x, e.getCollisionData().getPoint().x) << "Must store Point x coordinate";
  EXPECT_EQ(p.y, e.getCollisionData().getPoint().y) << "Must store Point y coordinate";
}
