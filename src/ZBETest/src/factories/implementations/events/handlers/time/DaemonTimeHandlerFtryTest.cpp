#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/zbe.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/events/handlers/TimeHandler.h"

#include "ZBE/events/handlers/time/DaemonTimeHandler.h"

#include "ZBE/factories/implementations/events/handlers/time/DaemonTimeHandlerFtry.h"

namespace DaemonTimeHandlerFtryTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): executed(false){}

  void run(){
    executed = true;
  }
  bool executed;
};

TEST(DaemonTimeHandlerFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto &dmnRsrc = RsrcStore<Daemon>::getInstance();
  auto &timeRsrc = RsrcStore<TimeHandler>::getInstance();
  auto &dmnTimeHandlerRsrc = RsrcStore<DaemonTimeHandler>::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["daemon"] = "dummydaemon";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  std::shared_ptr<DummyDaemon> daemon = std::make_shared<DummyDaemon>();
  dmnRsrc.insert("Daemon.dummydaemon"s, daemon);

  DaemonTimeHandlerFtry dthf;
  dthf.create("DaemonTimeHandlerFtryTestName", cfgId);
  dthf.setup("DaemonTimeHandlerFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("TimeHandler.DaemonTimeHandlerFtryTestName");
  std::shared_ptr<TimeHandler> outTH = timeRsrc.get(outId);

  uint64_t dthId = dict.get("DaemonTimeHandler.DaemonTimeHandlerFtryTestName");

  ASSERT_NE(0, outId) << "Must create a time handler with given name";
  ASSERT_NE(0, dthId) << "Must create a Daemon Time Handler with given name";

  EXPECT_FALSE(daemon->executed) << "Initially the daemon is not executed.";

  outTH->run(1);

  EXPECT_TRUE(daemon->executed) << "The daemon is executed.";

  configRsrc.clear();
  dict.clear();
  dmnRsrc.clear();
  timeRsrc.clear();
  dmnTimeHandlerRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace DaemonTimeHandlerFtryTest
