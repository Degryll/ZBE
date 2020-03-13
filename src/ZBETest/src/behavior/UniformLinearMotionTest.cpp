#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/time/Timer.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

namespace UniformLinearMotionTest {

class DummyTimer : public zbe::Timer {
  public:
    void start() {}
    int64_t stop() {return (0);}
    void reset() {}
    int64_t lapTime() {return (0);}
    int64_t totalTime() {return ((i++)*zbe::SECOND);}
    bool isRunning() {return (true);}

  private:
    int i = 0;
};

TEST(UniformLinearMotion2D, apply) {
    std::shared_ptr<zbe::SysTime> sysTime = zbe::SysTime::getInstance();
    sysTime->setMaxFrameTime(zbe::SECOND);

    auto sysTimer = std::make_shared<DummyTimer>();
    sysTime->setSystemTimer(sysTimer);

    std::shared_ptr<zbe::Entity> ent = std::make_shared<zbe::Entity>();
    std::shared_ptr<zbe::Value<zbe::Vector<2> > > pos = std::make_shared<zbe::SimpleValue<zbe::Vector<2> > >(zbe::Vector<2>{3.0, 5.0});
    std::shared_ptr<zbe::Value<zbe::Vector<2> > > vel = std::make_shared<zbe::SimpleValue<zbe::Vector<2> > >(zbe::Vector<2>{7.0, 11.0});

    ent->setVector2D(1, pos);
    ent->setVector2D(2, vel);

    zbe::UniformLinearMotion2D bulma;

    sysTime->update();
    sysTime->update();
    sysTime->setEventTime(zbe::SECOND);

    std::array<uint64_t, 2> a1{ {1, 2} };
    std::shared_ptr<zbe::MAvatar<zbe::Vector<2>, zbe::Vector<2> > > avatar = std::make_shared<zbe::MBaseAvatar<zbe::Vector<2>, zbe::Vector<2> > >(ent, a1);

    bulma.apply(avatar);

    EXPECT_EQ(10.0,pos->get()[0]) << "Position X.";
    EXPECT_EQ(16.0,pos->get()[1]) << "Position Y.";

    sysTime->update();
    sysTime->setEventTime(1.5*zbe::SECOND);

    bulma.apply(avatar);

    EXPECT_EQ(13.5,pos->get()[0]) << "Position X.";
    EXPECT_EQ(21.5,pos->get()[1]) << "Position Y.";
}

}  // namespace UniformLinearMotionTest
