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

#include "ZBE/factories/implementations/daemons/MasterDmnFtry.h"

namespace MasterDmnFtryTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): executed(false){}

  void run(){
    executed = true;
  }
  bool executed;
};

TEST(MasterDmnFtryTest, build) {
  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<json> &configRsrc = RsrcStore<json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();

  std::shared_ptr<json> cfg = std::make_shared<json>();
  (*cfg)["daemons"] = json::array({"dm1", "dm2", "dm3"});
  //json cfg = json::array({"dm1", "dm2", "dm3"});
  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  std::shared_ptr<DummyDaemon> dm1 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> dm2 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> dm3 = std::make_shared<DummyDaemon>();
  std::shared_ptr<DummyDaemon> dm4 = std::make_shared<DummyDaemon>();

  daemonRsrc.insert("Daemon.dm1"s, dm1);
  daemonRsrc.insert("Daemon.dm2"s, dm2);
  daemonRsrc.insert("Daemon.dm3"s, dm3);
  daemonRsrc.insert("Daemon.dm4"s, dm4);

  MasterDmnFtry mdf;
  mdf.create("MasterDmnFtryTestName", cfgId);
  mdf.setup("MasterDmnFtryTestName", cfgId);

  uint64_t outId = dict.get("Daemon.MasterDmnFtryTestName");
  std::shared_ptr<zbe::Daemon> outDmn = daemonRsrc.get(outId);

  ASSERT_NE(0, outId) << "Must create a daemon with given name";

  outDmn->run();

  EXPECT_TRUE(dm1->executed) << "Must call dm1";
  EXPECT_TRUE(dm2->executed) << "Must call dm2";
  EXPECT_TRUE(dm3->executed) << "Must call dm3";
  EXPECT_FALSE(dm4->executed) << "Must not call dm4";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace MasterDmnFtryTest
