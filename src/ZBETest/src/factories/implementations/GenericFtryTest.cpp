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

#include "ZBE/factories/implementations/GenericFtry.h"

namespace GenericFtryTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): executed(false) {}

  void run() override {
    executed = true;
  }
  bool executed;
};
//-----------------------
TEST(GenericFtryTest, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<json> &configRsrc = RsrcStore<json>::getInstance();
  RsrcStore<zbe::Daemon> &daemonRsrc = RsrcStore<zbe::Daemon>::getInstance();
  RsrcStore<DummyDaemon> &ddaemonRsrc = RsrcStore<DummyDaemon>::getInstance();

  GenericFtry<zbe::Daemon, DummyDaemon> gf("Daemon", "DummyDaemon");
  gf.create("GenericFtryTestName", 0);
  gf.setup("GenericFtryTestName", 0);

  std::shared_ptr<zbe::Daemon> outDmn = daemonRsrc.get("Daemon.GenericFtryTestName");
  std::shared_ptr<DummyDaemon> outDDmn = ddaemonRsrc.get("DummyDaemon.GenericFtryTestName");

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must create a daemon with given name";

  EXPECT_FALSE(outDDmn->executed) << "Initially outDDmn not called";

  outDmn->run();

  EXPECT_TRUE(outDDmn->executed) << "Must call outDDmn";

  configRsrc.clear();
  dict.clear();
  daemonRsrc.clear();
  ddaemonRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace GenericFtryTest
