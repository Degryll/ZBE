#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

#include "ZBE/core/events/generators/util/Reactor.h"

#include "ZBE/factories/implementations/events/handlers/actuators/DmnSelectorAtorFtry.h"

namespace DmnSelectorAtorFtryTest {

class DummyInteractionData {

};

class DummyInteractionObject {
};

class DummyAvatar {
public:
  using Base = void;
};

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): executed(false) {}

  void run(){
    executed = true;
  }
  bool executed;
};

typedef zbe::Reactor<DummyInteractionData, DummyInteractionObject, DummyAvatar> DummyReactor;

TEST(DaemonSelectorAlienAtorFtry, DISABLED_build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &actuatorRsrc = RsrcStore<DaemonSelectorAlienAtor<DummyAvatar, DummyReactor> >::getInstance();

  dict.insert("State.state1"s, 1);
  dict.insert("State.state2"s, 2);
  dict.insert("State.state3"s, 3);
  dict.insert("State.state4"s, 4);

  auto cfg = std::make_shared<json>();
  (*cfg)["daemons"] = json::array({
      {"dm1","state1"},
      {"dm2","state2"},
      {"dm3","state3"},
      {"dm4","state4"}
  });

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto dm1 = std::make_shared<DummyDaemon>();
  auto dm2 = std::make_shared<DummyDaemon>();
  auto dm3 = std::make_shared<DummyDaemon>();
  auto dm4 = std::make_shared<DummyDaemon>();

  uint64_t dm1Id = SysIdGenerator::getId();
  daemonRsrc.insert(dm1Id, dm1);
  dict.insert("Daemon.dm1"s, dm1Id);

  uint64_t dm2Id = SysIdGenerator::getId();
  daemonRsrc.insert(dm2Id, dm2);
  dict.insert("Daemon.dm2"s, dm2Id);

  uint64_t dm3Id = SysIdGenerator::getId();
  daemonRsrc.insert(dm3Id, dm3);
  dict.insert("Daemon.dm3"s, dm3Id);

  uint64_t dm4Id = SysIdGenerator::getId();
  daemonRsrc.insert(dm4Id, dm4);
  dict.insert("Daemon.dm4"s, dm4Id);

  DaemonSelectorAlienAtorFtry<DummyAvatar, DummyReactor> dsaaf;
  dsaaf.create("DaemonSelectorAlienAtorFtryTestName", cfgId);
  dsaaf.setup("DaemonSelectorAlienAtorFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Actuator.DaemonSelectorAlienAtorFtryTestName");
  auto outAtor= actuatorRsrc.get(outId);

  ASSERT_NE(0, outId) << "Must create a daemon with given name";

  outAtor->act();

  EXPECT_TRUE(dm1->executed) << "Must call dm1";
  EXPECT_TRUE(dm2->executed) << "Must call dm2";
  EXPECT_TRUE(dm3->executed) << "Must call dm3";
  EXPECT_FALSE(dm4->executed) << "Must not call dm4";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  actuatorRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateMachineDmnFtryTest
