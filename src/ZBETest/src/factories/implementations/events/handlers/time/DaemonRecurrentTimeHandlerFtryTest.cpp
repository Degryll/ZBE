#include "gtest/gtest.h"

#include <memory>

#include <nlohmann/json.hpp>

#include "ZBE/core/zbe.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

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

#include "ZBE/factories/implementations/events/handlers/time/DaemonRecurrentTimeHandlerFtry.h"

namespace DaemonRecurrentTimeHandlerFtryTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): runtimes(0){}

  void run(){
    runtimes++;
  }
  uint64_t runtimes;
};

TEST(DaemonRecurrentTimeHandlerFtry, run) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

//  using namespace zbe;
//  using namespace nlohmann;
//  using namespace std::string_literals;
//  auto &dict = NameRsrcDictionary::getInstance();
//  auto &configRsrc = RsrcStore<json>::getInstance();
//  auto &dmnRsrc = RsrcStore<Daemon>::getInstance();
//  auto &timeRsrc = RsrcStore<TimeHandler>::getInstance();
//  auto &tegRsrc = RsrcStore<TimeEventGenerator>::getInstance();
//  auto &avatarRsrc = RsrcStore<AvatarEntity<Avatar> >::getInstance();
//  auto &dmnRecurrentTimeHandlerRsrc = RsrcStore<DaemonRecurrentTimeHandler>::getInstance();
//
//  auto cfg = std::make_shared<json>();
//  (*cfg)["daemon"] = "dummydaemon";
//  (*cfg)["timeEventGenerator"] = "teg";
//  (*cfg)["avatar"] = "avatar";
//  (*cfg)["id"] = "drthf.id1";
//  (*cfg)["period"] = "drthf.period1";
//
//  uint64_t cfgId1 = SysIdGenerator::getId();
//  configRsrc.insert(cfgId1, cfg);
//
//  cfg = std::make_shared<json>();
//  (*cfg)["daemon"] = "dummydaemon";
//  (*cfg)["timeEventGenerator"] = "teg";
//  (*cfg)["avatar"] = "avatar";
//  (*cfg)["id"] = "drthf.id2";
//  (*cfg)["period"] = "drthf.period2";
//
//  uint64_t cfgId2 = SysIdGenerator::getId();
//  configRsrc.insert(cfgId2, cfg);
//
//  cfg = std::make_shared<json>();
//  (*cfg)["daemon"] = "dummydaemon";
//  (*cfg)["timeEventGenerator"] = "teg";
//  (*cfg)["avatar"] = "avatar";
//  (*cfg)["id"] = "drthf.id3";
//  (*cfg)["period"] = "drthf.period3";
//
//  uint64_t cfgId3 = SysIdGenerator::getId();
//  configRsrc.insert(cfgId3, cfg);
//
//  auto d = std::make_shared<DummyDaemon>();
//  dmnRsrc.insert("Daemon.dummydaemon"s, d);
//
//  std::shared_ptr<zbetest::MockedContextTime> contextTime = std::make_shared<zbetest::MockedContextTime>();
//  zbe::ContextTime::setMaxFrameTime(5000000);
//  contextTime->setFixedTime(0);
//  contextTime->update();
//  auto teg = std::make_shared<zbe::TimeEventGenerator>(3, contextTime);
//  tegRsrc.insert("timeEventGenerator.teg"s, teg);
//
////  auto *e = new zbe::Entity;
//  std::shared_ptr<zbe::Entity> e;
//  auto *ba = new zbe::BaseAvatar(e);
//  auto aefa = std::make_shared<zbe::AvatarEntityFixed<zbe::Avatar> >(ba);
//  avatarRsrc.insert("avatar.avatar"s, aefa);
//
//  dict.insert("drthf.id1"s, 42);
//  dict.insert("drthf.id2"s, 43);
//  dict.insert("drthf.id3"s, 44);
//  dict.insert("drthf.period1"s, zbe::TIME_QUANTUM * 1000);
//  dict.insert("drthf.period2"s, zbe::TIME_QUANTUM * 1500);
//  dict.insert("drthf.period3"s, zbe::TIME_QUANTUM *  500);
//
//  DaemonRecurrentTimeHandlerFtry dthf;
//  dthf.create("drth1", cfgId1);
//  dthf.create("drth2", cfgId2);
//  dthf.create("drth3", cfgId3);
//  dthf.setup("drth1", cfgId1);
//  dthf.setup("drth2", cfgId2);
//  dthf.setup("drth3", cfgId3);
//
//  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";
//
//  uint64_t th1Id = dict.get("TimeHandler.drth1");
//  uint64_t th2Id = dict.get("TimeHandler.drth2");
//  uint64_t th3Id = dict.get("TimeHandler.drth3");
//
//  uint64_t drth1Id = dict.get("DaemonRecurrentTimeHandler.drth1");
//  uint64_t drth2Id = dict.get("DaemonRecurrentTimeHandler.drth2");
//  uint64_t drth3Id = dict.get("DaemonRecurrentTimeHandler.drth3");
//
//  ASSERT_NE(0, th1Id) << "Must create the first time handler with given name";
//  ASSERT_NE(0, th2Id) << "Must create the second time handler with given name";
//  ASSERT_NE(0, th3Id) << "Must create the third time handler with given name";
//  ASSERT_NE(0, drth1Id) << "Must create the first Daemon Time Handler with given name";
//  ASSERT_NE(0, drth2Id) << "Must create the second Daemon Time Handler with given name";
//  ASSERT_NE(0, drth3Id) << "Must create the third Daemon Time Handler with given name";
//
//  std::shared_ptr<DaemonRecurrentTimeHandler> drth1 = dmnRecurrentTimeHandlerRsrc.get(drth1Id);
//  std::shared_ptr<DaemonRecurrentTimeHandler> drth2 = dmnRecurrentTimeHandlerRsrc.get(drth2Id);
//  std::shared_ptr<DaemonRecurrentTimeHandler> drth3 = dmnRecurrentTimeHandlerRsrc.get(drth3Id);
//
//  teg->addTimer(drth1, zbe::TIME_QUANTUM * 1000);
//  teg->addTimer(drth2, zbe::TIME_QUANTUM * 1500);
//  std::shared_ptr<zbe::TimerTicket> tt = teg->addTimer(drth3,  zbe::TIME_QUANTUM * 500);
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
//  EXPECT_EQ(0, d->runtimes) << "At time 800000 only drth3 should be triggered but is inactive, so no executions.";
//
//  contextTime->setFixedTime(zbe::TIME_QUANTUM * 2000);
//  contextTime->update();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(1, d->runtimes) << "Drth1 should be executed once, at 1000000.";
//
//  contextTime->setEventTime(zbe::TIME_QUANTUM * 1000);
//  contextTime->updateInitTime();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(2, d->runtimes) << "The second execution occurred at 1500000 (drth2).";
//
//  contextTime->setEventTime(zbe::TIME_QUANTUM * 1500);
//  contextTime->updateInitTime();
//  ba->setACTIVE(44);
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(4, d->runtimes) << "Two concurrent executions happened at 2000000 (drth1 and drth3, now active).";
//
//  contextTime->setEventTime(zbe::TIME_QUANTUM * 2000);
//  contextTime->updateInitTime();
//  contextTime->setFixedTime(zbe::TIME_QUANTUM * 5000);
//  contextTime->update();
//  teg->run();
//  es.manageCurrent();
//
//  EXPECT_EQ(5, d->runtimes) << "At 2500000 drth3 is triggered.";
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
//  dict.clear();
//  configRsrc.clear();
//  dmnRsrc.clear();
//  timeRsrc.clear();
//  tegRsrc.clear();
//  avatarRsrc.clear();
//  dmnRecurrentTimeHandlerRsrc.clear();
//
////  delete e;
//  //delete ba;  // AvatarEntityFixed deletes it

  zbe::SysError::clear();
}

}  // namespace DaemonRecurrentTimeHandlerFtryTest
