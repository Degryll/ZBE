#include "gtest/gtest.h"

#include <cstdint>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"

class R { // Reactor mock
  public:
    virtual ~R() {};
};

class C : public zbe::CollisionerCommon<C, R> {
  public:
    C(zbe::CollisionObject<R> * co):zbe::CollisionerCommon<C, R>(this, co, nullptr, 1) {};
};

TEST(CollisionSystemSolver, MovingCircleStaticAABB) {
  zbe::ConstantMovingCircle<R>* cc = new zbe::ConstantMovingCircle<R>(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));
  zbe::StaticAABB2D<R>* sbox = new zbe::StaticAABB2D<R>(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  C a(cc);
  C b(sbox);

  zbe::CollisionSelector<R> cs;

  bool result;
  zbe::Point2D p;
  uint64_t t = 1 * zbe::VELOCITYTOTIME;

  result = cs.select(a, b, t, p);
  EXPECT_EQ(1,result) << "First Moving Circle vs AABB collision.";
  EXPECT_DOUBLE_EQ(0.25 * zbe::VELOCITYTOTIME,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(2.75,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(5.0,p[1]) << "Point of collision (y).";

  // TODO mas test de colisiones y mas robustos
}

TEST(CollisionSystemSolver, StaticAABBMovingCircle) {
  zbe::ConstantMovingCircle<R>* cc= new zbe::ConstantMovingCircle<R>(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));
  zbe::StaticAABB2D<R>* sbox= new zbe::StaticAABB2D<R>(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  C a(cc);
  C b(sbox);

  zbe::CollisionSelector<R> cs;

  bool result;
  zbe::Point2D p;
  uint64_t t = 1 * zbe::VELOCITYTOTIME;

  result = cs.select(b, a, t, p);
  EXPECT_EQ(1,result) << "First Moving Circle vs AABB collision.";
  EXPECT_DOUBLE_EQ(0.25 * zbe::VELOCITYTOTIME,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(2.75,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(5.0,p[1]) << "Point of collision (y).";

  // TODO mas test de colisiones y mas robustos
}
