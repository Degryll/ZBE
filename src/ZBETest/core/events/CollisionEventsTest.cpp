#include "gtest/gtest.h"

#include "ZBE/core/events/CollisionEvent.h"
#include "ZBE/core/entities/CollisionerEntity.h"
#include "ZBE/core/tools/math/Point.h"

class CollisionerEntityTest : public zbe::CollisionerEntity {
};

TEST(CollisionEvent, Usage) {
  CollisionEntityTest a, b;
  Point2D p(4.0, 2.0);
  zbe::CollisionEvent e(1,100, &a, &b, p);
  EXPECT_EQ((uint64_t)1, e.getId()) << "Must store id";
  EXPECT_EQ((uint64_t)100, e.getTime()) << "Must store time";
  EXPECT_EQ(&a, e.getEntityA()) << "Must store EntityA";
  EXPECT_EQ(&b, e.getEntityB()) << "Must store EntityB";
  EXPECT_EQ(p.x, e.getPoint().x) << "Must store Point x coordinate";
  EXPECT_EQ(p.y, e.getPoint().y) << "Must store Point y coordinate";
}

