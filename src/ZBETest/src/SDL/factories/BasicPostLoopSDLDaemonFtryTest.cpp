#include "gtest/gtest.h"

#include <memory>
#include <string>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"

#include "ZBE/SDL/factories/daemons/BasicPostLoopSDLDaemonFtry.h"

namespace BasicPostLoopSDLDaemonFtryTest {

TEST(BasicPostLoopSDLDaemonFtry, Create) {
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
  auto& BasicPostLoopSDLDaemonRsrc = zbe::RsrcStore<zbe::BasicPostLoopSDLDaemon>::getInstance();

  auto win = std::make_shared<zbe::SDLWindow>();

  auto cfg = std::make_shared<json>();
  (*cfg)["window"] = "testwindow";
  sdlwinRsrc.insert("SDLWindow.testwindow", win);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  BasicPostLoopSDLDaemonFtry swdf;
  swdf.create("BasicPostLoopSDLDaemonFtryTestName", cfgId);
  swdf.setup("BasicPostLoopSDLDaemonFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("BasicPostLoopSDLDaemon.BasicPostLoopSDLDaemonFtryTestName");
  uint64_t dmnId = dict.get("Daemon.BasicPostLoopSDLDaemonFtryTestName");

  ASSERT_NE(0, outId) << "Must create a BasicPostLoopSDLDaemon with given name";
  ASSERT_NE(0, dmnId) << "Must create a Daemon with given name";

  std::shared_ptr<BasicPostLoopSDLDaemon> outpost = BasicPostLoopSDLDaemonRsrc.get(outId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  dict.clear();
  strStore.clear();
  intStore.clear();
  configRsrc.clear();
  sdlwinRsrc.clear();
  daemonRsrc.clear();
  BasicPostLoopSDLDaemonRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace BasicPostLoopSDLDaemonFtryTest
