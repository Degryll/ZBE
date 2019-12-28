#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/time/ContextTime.h"

#include "testutils/MockedContextTime.h"

#include "ZBE/events/handlers/time/DaemonRecurrentTimeHandler.h"

namespace DaemonRecurrentTimeHandlerTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): runtimes(0){}

  void run(){
    runtimes++;
  }
  uint64_t runtimes;
};

TEST(DaemonRecurrentTimeHandler, run) {
//  auto d = std::make_shared<DummyDaemon>();
//
//  std::shared_ptr<zbetest::MockedContextTime> contextTime = std::make_shared<zbetest::MockedContextTime>();
//  zbe::ContextTime::setMaxFrameTime(5000000);
//
//  contextTime->setFixedTime(0);
//  contextTime->update();
//
//  auto teg = std::make_shared<zbe::TimeEventGenerator>(3, contextTime);
//
////  auto *e = new zbe::Entity;
//  std::shared_ptr<zbe::Entity> e;
//  auto *ba = new zbe::BaseAvatar(e);
//  auto aefa = std::make_shared<zbe::AvatarEntityFixed<zbe::Avatar> >(ba);
//
//  auto dth1 = std::make_shared<zbe::DaemonRecurrentTimeHandler>(d, teg, aefa, 42, zbe::TIME_QUANTUM * 1000);
//  auto dth2 = std::make_shared<zbe::DaemonRecurrentTimeHandler>(d, teg, aefa, 43, zbe::TIME_QUANTUM * 1500);
//  auto dth3 = std::make_shared<zbe::DaemonRecurrentTimeHandler>(d, teg, aefa, 44,  zbe::TIME_QUANTUM * 500);
//
//  teg->addTimer(dth1, zbe::TIME_QUANTUM * 1000);
//  teg->addTimer(dth2, zbe::TIME_QUANTUM * 1500);
//  std::shared_ptr<zbe::TimerTicket> tt = teg->addTimer(dth3,  zbe::TIME_QUANTUM * 500);
//
//  ba->addTicket(44, tt);
//  ba->setINACTIVE(44);
//
//  zbe::EventStore &es = zbe::EventStore::getInstance();
//  es.clearStore();
//
//  EXPECT_EQ(0, d->runtimes) << "Initially the daemon is not executed.";
//
//
//  contextTime->setFixedTime(zbe::TIME_QUANTUM * 800);
//  contextTime->update();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(0, d->runtimes) << "At time 800000 only dth3 should be triggered but is inactive, so no executions.";
//
//  contextTime->setFixedTime(zbe::TIME_QUANTUM * 2000);
//  contextTime->update();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(1, d->runtimes) << "Dth1 should be executed once, at 1000000.";
//
//  contextTime->setEventTime(zbe::TIME_QUANTUM * 1000);
//  contextTime->updateInitTime();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(2, d->runtimes) << "The second execution occurred at 1500000 (dth2).";
//
//  contextTime->setEventTime(zbe::TIME_QUANTUM * 1500);
//  contextTime->updateInitTime();
//  ba->setACTIVE(44);
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(4, d->runtimes) << "Two concurrent executions happened at 2000000 (dth1 and dth3, now active).";
//
//  contextTime->setEventTime(zbe::TIME_QUANTUM * 2000);
//  contextTime->updateInitTime();
//  contextTime->setFixedTime(zbe::TIME_QUANTUM * 5000);
//  contextTime->update();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(5, d->runtimes) << "At 2500000 dth3 is triggered.";
//
//  contextTime->setEventTime(zbe::TIME_QUANTUM * 2500);
//  contextTime->updateInitTime();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(8, d->runtimes) << "The three recurrent timers triggered at 3000000.";
//
//  ba->setERASED(42);
//  ba->setERASED(43);
//  ba->setERASED(44);
//
//  contextTime->setEventTime(zbe::TIME_QUANTUM * 3000);
//  contextTime->updateInitTime();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(8, d->runtimes) << "No new execution, all timers all erased.";
//
////  delete e;
//  // delete ba;  // AvatarEntityFixed deletes it
}

}  // namespace DaemonRecurrentTimeHandlerTest
