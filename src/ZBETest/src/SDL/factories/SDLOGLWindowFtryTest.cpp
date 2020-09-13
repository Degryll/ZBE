#include "gtest/gtest.h"

#include <string>
#include <cstdint>

#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/SDL/factories/system/SDLOGLWindowFtry.h"

namespace SDLOGLWindowFtryTest {

TEST(SDLOGLWindowFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto &dict = NameRsrcDictionary::getInstance();
  auto& strStore = RsrcDictionary<std::string>::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto &configRsrc = RsrcStore<json>::getInstance();
  auto& SDLOGLWindowRsrc = zbe::RsrcStore<zbe::SDLOGLWindow>::getInstance();

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

  SDLOGLWindowFtry swdf;
  swdf.create("SDLOGLWindowFtryTestName", cfgId);
  swdf.setup("SDLOGLWindowFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("SDLOGLWindow.SDLOGLWindowFtryTestName");

  ASSERT_NE(0, outId) << "Must create a SDLOGLWindow with given name";

  std::shared_ptr<SDLOGLWindow> outSDLOGLW = SDLOGLWindowRsrc.get(outId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  dict.clear();
  strStore.clear();
  intStore.clear();
  configRsrc.clear();
  SDLOGLWindowRsrc.clear();

  zbe::SysError::clear();
}

}  // namespace SDLOGLWindowFtryTest
