#include "gtest/gtest.h"

#include <cstdint>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"
#include "ZBE/core/tools/math/collisions/ReactObject.h"

class R { // Reactor mock
  public:
    virtual ~R() {};
};

class RO : public zbe::ReactObject<R> {
  public:
    void act(R*) {}
};

class C : public zbe::CollisionerCommon<C, R> {
  public:
    C(std::shared_ptr<zbe::CollisionObject<R> > co):zbe::CollisionerCommon<C, R>(this, co, std::shared_ptr<zbe::ReactObject<R> >(new RO()), 1) {};
};

TEST(CollisionSystemSolver, MovingCircleStaticAABB) {
  //zbe::ConstantMovingCircle<R>* cc = new zbe::ConstantMovingCircle<R>(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));
  //zbe::StaticAABB2D<R>* sbox = new zbe::StaticAABB2D<R>(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
  std::shared_ptr<zbe::ConstantMovingCircle<R> > cc(new zbe::ConstantMovingCircle<R>(zbe::Circle({{200,300},100}), zbe::Vector2D({300,400})));
  std::shared_ptr<zbe::StaticSolidAABB2D<R> > sbox(new zbe::StaticSolidAABB2D<R>({{100,500},{600,1000}}));
  C a(cc);
  C b(sbox);

  zbe::CollisionSelector<R> cs;

  bool result;
  zbe::Point2D p;
  uint64_t t = 1 << zbe::PRECISION_DIGITS;

  result = cs.select(a, b, t, p);
  EXPECT_EQ(1,result) << "First Moving Circle vs AABB collision.";
  EXPECT_DOUBLE_EQ(25 << zbe::PRECISION_DIGITS,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(275,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(500,p[1]) << "Point of collision (y).";

  // TODO mas test de colisiones y mas robustos
}

TEST(CollisionSystemSolver, StaticSolidAABBMovingCircle) {
  std::shared_ptr<zbe::ConstantMovingCircle<R> > cc(new zbe::ConstantMovingCircle<R>(zbe::Circle({{200,300},100}), zbe::Vector2D({300,400})));
  std::shared_ptr<zbe::StaticSolidAABB2D<R> > sbox(new zbe::StaticSolidAABB2D<R>({{100,500},{600,1000}}));
  C a(cc);
  C b(sbox);

  zbe::CollisionSelector<R> cs;

  bool result;
  zbe::Point2D p;
  uint64_t t = 1 << zbe::PRECISION_DIGITS;

  result = cs.select(b, a, t, p);
  EXPECT_EQ(1,result) << "First Moving Circle vs AABB collision.";
  EXPECT_DOUBLE_EQ(25 << zbe::PRECISION_DIGITS,t) << "Time of collision.";
  EXPECT_DOUBLE_EQ(275,p[0]) << "Point of collision (x).";
  EXPECT_DOUBLE_EQ(500,p[1]) << "Point of collision (y).";
}

TEST(CollisionSystemSolver, DISABLED_MoreTests) {
  // TODO mas test de colisiones y mas robustos. No olvidar los objetos que faltan.
}
