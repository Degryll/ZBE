#include "gtest/gtest.h"

#include <memory>
#include <string>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

#include "ZBE/SDL/factories/daemons/BasicPreLoopSDLDaemonFtry.h"

namespace BasicPreLoopSDLDaemonFtryTest {

TEST(BasicPreLoopSDLDaemonFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto& strStore = RsrcDictionary<std::string>::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto& sdlwinRsrc = zbe::RsrcStore<zbe::SDLWindow>::getInstance();
  auto& daemonRsrc = zbe::RsrcStore<zbe::Daemon>::getInstance();
  auto& BasicPreLoopSDLDaemonRsrc = zbe::RsrcStore<zbe::BasicPreLoopSDLDaemon>::getInstance();

  auto win = std::make_shared<zbe::SDLWindow>();

  auto cfg = std::make_shared<json>();
  (*cfg)["window"] = "testwindow";
  sdlwinRsrc.insert("SDLWindow.testwindow", win);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  BasicPreLoopSDLDaemonFtry swdf;
  swdf.create("BasicPreLoopSDLDaemonFtryTestName", cfgId);
  swdf.setup("BasicPreLoopSDLDaemonFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("BasicPreLoopSDLDaemon.BasicPreLoopSDLDaemonFtryTestName");
  uint64_t dmnId = dict.get("Daemon.BasicPreLoopSDLDaemonFtryTestName");

  ASSERT_NE(0, outId) << "Must create a BasicPreLoopSDLDaemon with given name";
  ASSERT_NE(0, dmnId) << "Must create a Daemon with given name";

  std::shared_ptr<BasicPreLoopSDLDaemon> outpre = BasicPreLoopSDLDaemonRsrc.get(outId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  dict.clear();
  strStore.clear();
  intStore.clear();
  configRsrc.clear();
  sdlwinRsrc.clear();
  daemonRsrc.clear();
  BasicPreLoopSDLDaemonRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace BasicPreLoopSDLDaemonFtryTest
