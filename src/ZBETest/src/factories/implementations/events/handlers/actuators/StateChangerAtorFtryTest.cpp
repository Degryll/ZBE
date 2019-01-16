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

#include "ZBE/factories/implementations/events/handlers/actuators/StateChangerAtorFtry.h"

namespace StateChangerAtorFtryTest {

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

typedef zbe::Reactor<DummyInteractionData, DummyInteractionObject, A, zbe::Stated> DummyReactor;

TEST(StateChangerSelfAtorFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcDictionary<int64_t> &intDictionary = RsrcDictionary<int64_t>::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &actuatorRsrc = RsrcStore<Actuator<zbe::WeakAvatarEntityContainer<zbe::Stated>, DummyReactor> >::getInstance();
  auto &dsaRsrc = RsrcStore<StateChangerSelfAtor<A, DummyReactor> >::getInstance();

  intDictionary.insert("State.state1"s, 7);

  auto cfg = std::make_shared<json>();
  (*cfg)["state"] = "State.state1";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  StateChangerSelfAtorFtry<A, DummyReactor> dssaf;
  dssaf.create("StateChangerSelfAtorFtryTestName", cfgId);
  dssaf.setup("StateChangerSelfAtorFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Actuator.StateChangerSelfAtorFtryTestName");
  uint64_t outRealId = dict.get("StateChangerSelfAtor.StateChangerSelfAtorFtryTestName");
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

  EXPECT_EQ(s->getState(),7) << "New state must match";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  actuatorRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateMachineDmnFtryTest
