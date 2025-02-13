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

#include "ZBE/factories/implementations/events/handlers/input/DaemonClickIHFtry.h"

namespace DaemonClickIHFtryTest {

class DummyDaemon : public zbe::Daemon {
public:
  DummyDaemon(): executed(false) {}

  void run() override {
    executed = true;
  }
  bool executed;
};

TEST(DaemonClickIHFtry, build) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  auto &inputRsrc = RsrcStore<InputHandler>::getInstance();
  auto &dcihRsrc = RsrcStore<DaemonClickIH>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &valueDRsrc = RsrcStore<Value<double> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg) = {
              {"daemon", "dm1"},
              {"x", 10},
              {"y", 10},
              {"h", 100},
              {"w", 100},
              {"xval", "dchixval"},
              {"yval", "dchiyval"}
            };

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  auto dm1 = std::make_shared<DummyDaemon>();
  auto xval = std::make_shared<SimpleValue<double> >(15.0);
  auto yval = std::make_shared<SimpleValue<double> >(15.0);

  daemonRsrc.insert("Daemon."s + "dm1", dm1);

  valueDRsrc.insert("ValueD."s + "dchixval"s, xval);
  valueDRsrc.insert("ValueD."s + "dchiyval"s, yval);

  DaemonClickIHFtry dcihf;
  dcihf.create("DaemonClickIHFtryTestName", cfgId);
  dcihf.setup("DaemonClickIHFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("InputHandler.DaemonClickIHFtryTestName");
  uint64_t outRealId = dict.get("DaemonClickIH.DaemonClickIHFtryTestName");

  ASSERT_NE(0, outId) << "Must create a InputHandler with given name";
  ASSERT_NE(0, outRealId) << "Must create a DaemonClickIH with given name";

  auto outHnd = inputRsrc.get(outId);

  EXPECT_FALSE(dm1->executed) << "Initially daemon not called";

  outHnd->run(1, 0.0f);

  EXPECT_TRUE(dm1->executed) << "Daemon called after run";

  dm1->executed = false;
  xval->set(0);
  yval->set(0);

  outHnd->run(1, 0.0f);

  EXPECT_FALSE(dm1->executed) << "Daemon not called after run out of bounds";

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
