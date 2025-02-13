#include "gtest/gtest.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/factories/implementations/events/handlers/input/DaemonIHFtry.h"

namespace DaemonIHFtryTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): executed(false) {}

  void run() override {
    executed = true;
  }
  bool executed;
};

TEST(DaemonIHFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  auto &inputRsrc = RsrcStore<InputHandler>::getInstance();
  auto &dcihRsrc = RsrcStore<DaemonIH>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &valueDRsrc = RsrcStore<Value<double> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg) = {{"daemon", "dm1"}};

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto dm1 = std::make_shared<DummyDaemon>();

  daemonRsrc.insert("Daemon."s + "dm1", dm1);

  DaemonIHFtry dcihf;
  dcihf.create("DaemonIHFtryTestName", cfgId);
  dcihf.setup("DaemonIHFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("InputHandler.DaemonIHFtryTestName");
  uint64_t outRealId = dict.get("DaemonIH.DaemonIHFtryTestName");

  ASSERT_NE(0, outId) << "Must create a InputHandler with given name";
  ASSERT_NE(0, outRealId) << "Must create a DaemonIH with given name";

  auto outHnd = inputRsrc.get(outId);

  EXPECT_FALSE(dm1->executed) << "Initially daemon not called";

  outHnd->run(1, 0.0f);

  EXPECT_TRUE(dm1->executed) << "Daemon called after run";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Finaly no errors.";

  dict.clear();
  configRsrc.clear();
  inputRsrc.clear();
  dcihRsrc.clear();
  daemonRsrc.clear();
  valueDRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace StateMachineDmnFtryTest
