#include "gtest/gtest.h"

#include <string>
#include <cstdint>

#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/factories/system/SDLWindowFtry.h"

namespace SDLWindowFtryTest {

TEST(SDLWindowFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto& strStore = RsrcDictionary<std::string>::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto& SDLWindowRsrc = zbe::RsrcStore<zbe::SDLWindow>::getInstance();

  auto cfg = std::make_shared<json>();
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

  SDLWindowFtry swdf;
  swdf.create("SDLWindowFtryTestName", cfgId);
  swdf.setup("SDLWindowFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("SDLWindow.SDLWindowFtryTestName");

  ASSERT_NE(0, outId) << "Must create a SDLWindow with given name";

  std::shared_ptr<SDLWindow> outSDLW = SDLWindowRsrc.get(outId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  dict.clear();
  strStore.clear();
  intStore.clear();
  configRsrc.clear();
  SDLWindowRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace SDLWindowFtryTest
