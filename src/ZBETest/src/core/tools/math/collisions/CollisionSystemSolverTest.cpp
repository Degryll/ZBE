#include "gtest/gtest.h"

#include <cstdint>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"
#include "ZBE/core/events/generators/util/ReactObject.h"

//class R { // Reactor mock
//  public:
//    virtual ~R() {};
//};
//
//class RO : public zbe::ReactObject<R> {
//  public:
//    void act(R*) {}
//};
//
//class C : public zbe::InteractionerCommon<C, R> {
//  public:
//    C(std::shared_ptr<zbe::CollisionObject<R> > co):zbe::InteractionerCommon<C, R>(this, co, std::shared_ptr<zbe::ReactObject<R> >(new RO()), 1) {};
//};

TEST(CollisionSystemSolver, DISABLED_MovingCircleStaticSolidAABB) {
//  //zbe::ConstantMovingCircle* cc = new zbe::ConstantMovingCircle(zbe::Circle({{2.0,3.0},1.0}),zbe::Vector2D({3.0,4.0}));
//  //zbe::StaticAABB2D<R>* sbox = new zbe::StaticAABB2D<R>(zbe::AABB2D({{1.0,5.0},{6.0,10.0}}));
//  std::shared_ptr<zbe::ConstantMovingCircle > cc(new zbe::ConstantMovingCircle(zbe::Circle({{20.0,30.0},10.0}), zbe::Vector2D({30.0,40.0})));
//  std::shared_ptr<zbe::StaticSolidAABB2D > sbox(new zbe::StaticSolidAABB2D({{10.0,50.0},{60.0,100.0}}));
//  C a(cc);
//  C b(sbox);
//
//  zbe::CollisionSelector* cs = new zbe::BaseCollisionSelector();
//
//  bool result;
//  zbe::Point2D p;
//  int64_t t = zbe::SECOND;
//
//  result = cs->select(a, b, t, p);
//  int64_t expectedTime = zbe::quantizeTime(zbe::SECOND / 4);
//  EXPECT_TRUE(result) << "First Moving Circle vs AABB collision.";
//  EXPECT_DOUBLE_EQ(expectedTime, t) << "Time of collision.";
//  EXPECT_DOUBLE_EQ(27.5, p[0]) << "Point of collision (x).";
//  EXPECT_DOUBLE_EQ(50.0, p[1]) << "Point of collision (y).";
}

TEST(CollisionSystemSolver, DISABLED_StaticSolidAABBMovingCircle) {
//  std::shared_ptr<zbe::ConstantMovingCircle > cc(new zbe::ConstantMovingCircle(zbe::Circle({{200,300},100}), zbe::Vector2D({300,400})));
//  std::shared_ptr<zbe::StaticSolidAABB2D > sbox(new zbe::StaticSolidAABB2D({{100,500},{600,1000}}));
//  C a(cc);
//  C b(sbox);
//
//  zbe::CollisionSelector* cs = new zbe::BaseCollisionSelector();
//
//  bool result;
//  zbe::Point2D p;
//  int64_t t = zbe::SECOND;
//
//  result = cs->select(b, a, t, p);
//  int64_t expectedTime = zbe::quantizeTime(zbe::SECOND / 4);
//  EXPECT_TRUE(result) << "First Moving Circle vs AABB collision.";
//  EXPECT_DOUBLE_EQ(expectedTime, t) << "Time of collision.";
//  EXPECT_DOUBLE_EQ(275,p[0]) << "Point of collision (x).";
//  EXPECT_DOUBLE_EQ(500,p[1]) << "Point of collision (y).";
}

TEST(CollisionSystemSolver, DISABLED_MoreTests) {
  // TODO mas test de colisiones y mas robustos. No olvidar los objetos que faltan.
}
