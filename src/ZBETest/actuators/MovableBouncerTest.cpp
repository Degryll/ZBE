#include "gtest/gtest.h"

#include "ZBE/actuators/MovableBouncer.h"
#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/entities/avatars/Bounceable.h"
#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/implementations/SimpleBounceable.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/collisions/ReactObject.h"
#include "ZBE/core/tools/math/collisions/CollisionData.h"

class ReactorMock {
  public:
      virtual ~ReactorMock() {}
      virtual void act(zbe::Bounceable*) {};
};

class ReactObjectMock : public zbe::SimpleBounceable, public zbe::ReactObjectCommon<zbe::SimpleBounceable, ReactorMock> {
  public:
    ReactObjectMock(double factor) : zbe::SimpleBounceable(factor), zbe::ReactObjectCommon<zbe::SimpleBounceable, ReactorMock>(this) {}
};

TEST(MovableBouncer, DISABLED_run) {
//    ReactObjectMock ro(1.0);
//    zbe::SimpleMobile<2> mb({0.0,0.0},{1.0,0.0});
//    zbe::BaseMovable<ReactorMock, 2> mv(&mb);
//    zbe::CollisionData cd({1.0,1.0});
//    zbe::MovableBouncer<ReactorMock,2> mBouncer;
//    mBouncer.run(&mv, &ro, &cd);
//
//    EXPECT_NEAR(0.0,mb.getVelocity().x,0.00001) << "bounce velocity \".x\".";
//    EXPECT_NEAR(-1.0,mb.getVelocity().y,0.00001) << "bounce velocity \".y\".";
}

