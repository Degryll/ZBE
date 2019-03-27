#include "gtest/gtest.h"

#include <string>
#include <cstdint>

#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/SDL/daemons/SDLWindowDaemon.h"

#include "ZBE/SDL/factories/SDLWindowDmnFtry.h"

namespace SDLWindowDmnFtryTest {

TEST(SDLWindowDmnFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto& strStore = RsrcDictionary<std::string>::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto& SDLWindowDmnRsrc = zbe::RsrcStore<zbe::SDLWindowDaemon>::getInstance();
  auto &dmnRsrc = RsrcStore<zbe::Daemon>::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["name"] = "testname";
  strStore.insert("testname", "window.name");
  (*cfg)["title"] = "testtitle";
  strStore.insert("testtitle", "window.title");
  (*cfg)["x"] = "testx";
  intStore.insert("testx", 0);
  (*cfg)["y"] = "testy";
  intStore.insert("testy", 0);
  (*cfg)["w"] = "testw";
  intStore.insert("testw", 100);
  (*cfg)["h"] = "testh";
  intStore.insert("testh", 100);
  (*cfg)["wflags"] = "testwflags";
  intStore.insert("testwflags", 0);
  (*cfg)["rflags"] = "testrflags";
  intStore.insert("testrflags", 0);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  SDLWindowDmnFtry swdf;
  swdf.create("SDLWindowDmnFtryTestName", cfgId);
  swdf.setup("SDLWindowDmnFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Daemon.SDLWindowDmnFtryTestName");
  uint64_t swdId = dict.get("SDLWindowDaemon.SDLWindowDmnFtryTestName");

  ASSERT_NE(0, outId) << "Must create a Daemon with given name";
  ASSERT_NE(0, swdId) << "Must create a SDLWindowDaemon with given name";

  std::shared_ptr<Daemon> outDmn = dmnRsrc.get(outId);
  std::shared_ptr<SDLWindowDaemon> outSDLWDmn = SDLWindowDmnRsrc.get(swdId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  dict.clear();
  strStore.clear();
  intStore.clear();
  configRsrc.clear();
  SDLWindowDmnRsrc.clear();
  dmnRsrc.clear();

  zbe::SysError::clear();
}
}  // namespace SDLWindowDmnFtryTest
