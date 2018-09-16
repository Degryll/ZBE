#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

#include "ZBE/factories/implementations/daemons/StateMachineDmnFtry.h"

namespace StateMachineDmnFtryTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(std::shared_ptr<zbe::Value<int64_t> > state, int64_t newstate): executed(false), state(state), newstate(newstate) {}

  void run(){
    executed = true;
    state->set(newstate);
  }
  bool executed;
  std::shared_ptr<zbe::Value<int64_t> > state;
  int64_t newstate;
};

TEST(StateMachineDmnFtryTest, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<json> &configRsrc = RsrcStore<json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Value<int64_t> > &valueRsrc = RsrcStore<Value<int64_t> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["daemons"] = json::array({
      {"dm1",1},
      {"dm2",2},
      {"dm3",3},
      {"dm4",4}
  });
  (*cfg)["state"] = "machineState";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto state = std::make_shared<SimpleValue<int64_t> >(1);
  uint64_t valueId = SysIdGenerator::getId();
  valueRsrc.insert(valueId, state);
  dict.insert("Valueu.machineState"s, valueId);

  auto dm1 = std::make_shared<DummyDaemon>(state, 2);
  auto dm2 = std::make_shared<DummyDaemon>(state, 3);
  auto dm3 = std::make_shared<DummyDaemon>(state, 5);
  auto dm4 = std::make_shared<DummyDaemon>(state, 1);

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

  StateMachineDmnFtry mdf;
  mdf.build("StateMachineDmnFtryTestName", cfgId);

  //EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";
  printf("Error: %s", zbe::SysError::getFirstErrorString().c_str());


  uint64_t outId = dict.get("Daemon.StateMachineDmnFtryTestName");
  std::shared_ptr<zbe::Daemon> outDmn = daemonRsrc.get(outId);

  ASSERT_NE(0, outId) << "Must create a daemon with given name";

  outDmn->run();

  EXPECT_TRUE(dm1->executed) << "Must call dm1";
  EXPECT_TRUE(dm2->executed) << "Must call dm2";
  EXPECT_TRUE(dm3->executed) << "Must call dm3";
  EXPECT_FALSE(dm4->executed) << "Must not call dm4";

  dm1->executed = false;
  dm2->executed = false;
  dm3->executed = false;
  dm4->executed = false;

  state->set(3);

  dm1->newstate = 4;
  dm2->newstate = 0;
  dm3->newstate = 1;
  dm4->newstate = 2;

  outDmn->run();

  EXPECT_TRUE(dm1->executed) << "Must call dm1";
  EXPECT_TRUE(dm2->executed) << "Must call dm2";
  EXPECT_TRUE(dm3->executed) << "Must call dm3";
  EXPECT_TRUE(dm4->executed) << "Must call dm4";

  dm1->executed = false;
  dm2->executed = false;
  dm3->executed = false;
  dm4->executed = false;

  state->set(0);

  dm1->newstate = 4;
  dm2->newstate = 0;
  dm3->newstate = 1;
  dm4->newstate = 2;

  outDmn->run();

  EXPECT_FALSE(dm1->executed) << "Must not call dm1";
  EXPECT_FALSE(dm2->executed) << "Must not call dm2";
  EXPECT_FALSE(dm3->executed) << "Must not call dm3";
  EXPECT_FALSE(dm4->executed) << "Must not call dm4";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  valueRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateMachineDmnFtryTest
