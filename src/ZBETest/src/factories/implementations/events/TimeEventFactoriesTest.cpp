#include "gtest/gtest.h"
#include <memory>

#include <nlohmann/json.hpp>

#include "ZBE/core/tools/time/ContextTime.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/events/handlers/time/DaemonTimeHandler.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/factories/implementations/events/generators/TimeEventGnFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/DaemonTimeHandlerFtry.h"

#include "testutils/MockedContextTime.h"

namespace TimeEventFactoriesTest {

struct DummyDaemon : public zbe::Daemon {
  DummyDaemon() : executed(false) {}
  void run() {
    executed = true;
  }

  bool executed;
};

TEST(TimeEventFactories, Event) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";
  using namespace std::string_literals;
  using namespace nlohmann;

  auto tegF = std::make_shared<zbe::TimeEventGnFtry>();
  auto dthF = std::make_shared<zbe::DaemonTimeHandlerFtry>();

  auto& configRsrc = zbe::RsrcStore<nlohmann::json>::getInstance();
  auto& cxTimeStore = zbe::RsrcStore<zbe::ContextTime>::getInstance();
  auto& dmnRsrc = zbe::RsrcStore<zbe::Daemon>::getInstance();
  auto& dmnTimeHandlerRsrc = zbe::RsrcStore<zbe::DaemonTimeHandler>::getInstance();
  auto& tegRsrc = zbe::RsrcStore<zbe::TimeEventGenerator>::getInstance();
  auto& intStore = zbe::RsrcDictionary<int64_t>::getInstance();

  intStore.insert("eI1", 42);
  intStore.insert("t1", 5500);

  std::shared_ptr<zbetest::MockedContextTime> cxTime = std::make_shared<zbetest::MockedContextTime>();
  cxTimeStore.insert("ContextTime.cT1", cxTime);

  std::shared_ptr<json> tegCfg = std::make_shared<json>();
  (*tegCfg)["eventId"] = "eI1"s;
  (*tegCfg)["contextTime"] = "cT1"s;

  uint64_t tegCfgId = zbe::SysIdGenerator::getId();
  configRsrc.insert(tegCfgId, tegCfg);

  tegF->create("tegname", tegCfgId);
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "After teg create no errors.";

  tegF->setup("tegname", tegCfgId);
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "After teg setup no errors.";

  std::shared_ptr<DummyDaemon> dd1 = std::make_shared<DummyDaemon>();
  dmnRsrc.insert("Daemon.dmn1", dd1);

  std::shared_ptr<json> dthCfg = std::make_shared<json>();
  (*dthCfg)["dmn"] = "dmn1";
  (*dthCfg)["generator"] = "tegname";
  (*dthCfg)["time"] = "t1";

  uint64_t dthCfgId = zbe::SysIdGenerator::getId();
  configRsrc.insert(dthCfgId, dthCfg);

  dthF->create("dthname", dthCfgId);
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "After dth create no errors.";
  dthF->setup("dthname", dthCfgId);
  //zbe::SysError::getFirstErrorString()
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "After dth setup no errors.";

  zbe::ContextTime::setMaxFrameTime(5000000);

  cxTime->setFixedTime(0);
  cxTime->update();

  zbe::EventStore &es = zbe::EventStore::getInstance();
  es.clearStore();

  EXPECT_FALSE(dd1->executed) << "dd1 must not be called";

  cxTime->setFixedTime(2000000);
  cxTime->update();

  auto teg = tegRsrc.get("TimeEventGenerator.tegname");

  teg->run();
  es.manageCurrent();

  EXPECT_TRUE(dd1->executed) << "dd1 should be called";

  es.clearStore();

  configRsrc.clear();
  cxTimeStore.clear();
  dmnRsrc.clear();
  dmnTimeHandlerRsrc.clear();
  tegRsrc.clear();
  intStore.clear();
}

}  // namespace TimeEventGeneratorTest
