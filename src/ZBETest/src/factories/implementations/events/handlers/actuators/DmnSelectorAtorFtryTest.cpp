#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

#include "ZBE/core/events/generators/util/Reactor.h"

#include "ZBE/entities/avatars/Stated.h"

#include "ZBE/factories/implementations/events/handlers/actuators/DmnSelectorAtorFtry.h"

namespace DmnSelectorAtorFtryTest {

class DummyStated : virtual public zbe::Stated {
public:
    DummyStated(int64_t state) : state(state) {}
    void setState(int64_t state) {this->state = state;}
    void add(int64_t value) {this->state += value;}
    int64_t getState() {return this->state;}
    int64_t state;
};

class DummyInteractionData {

};

class DummyInteractionObject {
};

class A {
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

typedef zbe::Reactor<DummyInteractionData, DummyInteractionObject, A, zbe::Stated> DummyReactor;

TEST(DaemonSelectorAlienAtorFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &actuatorRsrc = RsrcStore<Actuator<zbe::WeakAvatarEntityContainer<A>, DummyReactor> >::getInstance();
  auto &dsaRsrc = RsrcStore<DaemonSelectorAlienAtor<A, DummyReactor> >::getInstance();

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
  (*cfg)["defdmn"] = "dm0";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto dm0 = std::make_shared<DummyDaemon>();
  auto dm1 = std::make_shared<DummyDaemon>();
  auto dm2 = std::make_shared<DummyDaemon>();
  auto dm3 = std::make_shared<DummyDaemon>();
  auto dm4 = std::make_shared<DummyDaemon>();

  daemonRsrc.insert("Daemon.dm0"s, dm0);
  daemonRsrc.insert("Daemon.dm1"s, dm1);
  daemonRsrc.insert("Daemon.dm2"s, dm2);
  daemonRsrc.insert("Daemon.dm3"s, dm3);
  daemonRsrc.insert("Daemon.dm4"s, dm4);

  DaemonSelectorAlienAtorFtry<A, DummyReactor> dsaaf;
  dsaaf.create("DaemonSelectorAlienAtorFtryTestName", cfgId);
  dsaaf.setup("DaemonSelectorAlienAtorFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Actuator.DaemonSelectorAlienAtorFtryTestName");
  uint64_t outRealId = dict.get("DaemonSelectorAlienAtor.DaemonSelectorAlienAtorFtryTestName");
  auto outAtor= actuatorRsrc.get(outId);
  auto outRealAtor= dsaRsrc.get(outRealId);

  ASSERT_NE(0, outId) << "Must create a daemon with given name";

  // Collisioner
  A *a = new A();
  std::shared_ptr<zbe::AvatarEntity<A> > aea = std::make_shared<zbe::AvatarEntityFixed<A> >(a);
  auto waeca = std::make_shared<zbe::WeakAvatarEntityContainer<A> >(aea);

  // react object
  zbe::Stated *s = new DummyStated(1);
  std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aes = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(s);
  auto waecs = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Stated> >(aes);
  std::shared_ptr<zbe::ReactObject<DummyReactor> > ro = std::make_shared<zbe::ReactObjectCommon<DummyReactor, zbe::Stated> > (waecs);
  // cd
  DummyInteractionData* diData = new DummyInteractionData();
  std::shared_ptr<Actuator<zbe::WeakAvatarEntityContainer<A>, DummyReactor> > outAtorCast = outRealAtor;
  outAtor->run(waeca, ro,  diData);

  EXPECT_TRUE(dm1->executed) << "Must call dm1";
  EXPECT_FALSE(dm2->executed) << "Must not call dm2";
  EXPECT_FALSE(dm3->executed) << "Must not call dm3";
  EXPECT_FALSE(dm4->executed) << "Must not call dm4";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  actuatorRsrc.clear();

  zbe::SysError::clear();
}

TEST(DaemonSelectorSelfAtorFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &actuatorRsrc = RsrcStore<Actuator<zbe::WeakAvatarEntityContainer<zbe::Stated>, DummyReactor> >::getInstance();
  auto &dsaRsrc = RsrcStore<DaemonSelectorSelfAtor<A, DummyReactor> >::getInstance();

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
  (*cfg)["defdmn"] = "dm0";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto dm0 = std::make_shared<DummyDaemon>();
  auto dm1 = std::make_shared<DummyDaemon>();
  auto dm2 = std::make_shared<DummyDaemon>();
  auto dm3 = std::make_shared<DummyDaemon>();
  auto dm4 = std::make_shared<DummyDaemon>();

  daemonRsrc.insert("Daemon.dm0"s, dm0);
  daemonRsrc.insert("Daemon.dm1"s, dm1);
  daemonRsrc.insert("Daemon.dm2"s, dm2);
  daemonRsrc.insert("Daemon.dm3"s, dm3);
  daemonRsrc.insert("Daemon.dm4"s, dm4);

  DaemonSelectorSelfAtorFtry<A, DummyReactor> dssaf;
  dssaf.create("DaemonSelectorSelfAtorFtryTestName", cfgId);
  dssaf.setup("DaemonSelectorSelfAtorFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Actuator.DaemonSelectorSelfAtorFtryTestName");
  uint64_t outRealId = dict.get("DaemonSelectorSelfAtor.DaemonSelectorSelfAtorFtryTestName");
  auto outAtor= actuatorRsrc.get(outId);
  auto outRealAtor= dsaRsrc.get(outRealId);

  ASSERT_NE(0, outId) << "Must create a daemon with given name";

  // Collisioner
  A *a = new A();
  std::shared_ptr<zbe::AvatarEntity<A> > aea = std::make_shared<zbe::AvatarEntityFixed<A> >(a);
  auto waeca = std::make_shared<zbe::WeakAvatarEntityContainer<A> >(aea);

  // react object
  zbe::Stated *s = new DummyStated(1);
  std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aes = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(s);
  auto waecs = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Stated> >(aes);
  // cd
  DummyInteractionData* diData = new DummyInteractionData();
  std::shared_ptr<Actuator<zbe::WeakAvatarEntityContainer<zbe::Stated>, DummyReactor> > outAtorCast = outRealAtor;
  std::shared_ptr<zbe::ReactObject<DummyReactor> > ro = std::make_shared<zbe::ReactObjectCommon<DummyReactor, A> > (waeca);
  outAtor->run(waecs, ro,  diData);

  EXPECT_TRUE(dm1->executed) << "Must call dm1";
  EXPECT_FALSE(dm2->executed) << "Must not call dm2";
  EXPECT_FALSE(dm3->executed) << "Must not call dm3";
  EXPECT_FALSE(dm4->executed) << "Must not call dm4";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  actuatorRsrc.clear();

  zbe::SysError::clear();
}

TEST(DaemonSelectorSelfAnyAtorFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &actuatorRsrc = RsrcStore<Actuator<zbe::WeakAvatarEntityContainer<zbe::Stated>, DummyReactor> >::getInstance();
  auto &dsaRsrc = RsrcStore<DaemonSelectorSelfAnyAtor<DummyReactor> >::getInstance();

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
  (*cfg)["defdmn"] = "dm0";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto dm0 = std::make_shared<DummyDaemon>();
  auto dm1 = std::make_shared<DummyDaemon>();
  auto dm2 = std::make_shared<DummyDaemon>();
  auto dm3 = std::make_shared<DummyDaemon>();
  auto dm4 = std::make_shared<DummyDaemon>();

  daemonRsrc.insert("Daemon.dm0"s, dm0);
  daemonRsrc.insert("Daemon.dm1"s, dm1);
  daemonRsrc.insert("Daemon.dm2"s, dm2);
  daemonRsrc.insert("Daemon.dm3"s, dm3);
  daemonRsrc.insert("Daemon.dm4"s, dm4);

  DaemonSelectorSelfAtorFtry<A, DummyReactor> dssaf;
  dssaf.create("DaemonSelectorSelfAtorFtryTestName", cfgId);
  dssaf.setup("DaemonSelectorSelfAtorFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Actuator.DaemonSelectorSelfAtorFtryTestName");
  uint64_t outRealId = dict.get("DaemonSelectorSelfAtor.DaemonSelectorSelfAtorFtryTestName");
  auto outAtor= actuatorRsrc.get(outId);
  auto outRealAtor= dsaRsrc.get(outRealId);

  ASSERT_NE(0, outId) << "Must create a daemon with given name";

  // Collisioner
  A *a = new A();
  std::shared_ptr<zbe::AvatarEntity<A> > aea = std::make_shared<zbe::AvatarEntityFixed<A> >(a);
  auto waeca = std::make_shared<zbe::WeakAvatarEntityContainer<A> >(aea);

  // react object
  zbe::Stated *s = new DummyStated(1);
  std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aes = std::make_shared<zbe::AvatarEntityFixed<zbe::Stated> >(s);
  auto waecs = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Stated> >(aes);
  // cd
  DummyInteractionData* diData = new DummyInteractionData();
  std::shared_ptr<Actuator<zbe::WeakAvatarEntityContainer<zbe::Stated>, DummyReactor> > outAtorCast = outRealAtor;
  std::shared_ptr<zbe::ReactObject<DummyReactor> > ro = std::make_shared<zbe::ReactObjectCommon<DummyReactor, A> > (waeca);
  outAtor->run(waecs, ro,  diData);

  EXPECT_TRUE(dm1->executed) << "Must call dm1";
  EXPECT_FALSE(dm2->executed) << "Must not call dm2";
  EXPECT_FALSE(dm3->executed) << "Must not call dm3";
  EXPECT_FALSE(dm4->executed) << "Must not call dm4";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  actuatorRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateMachineDmnFtryTest
