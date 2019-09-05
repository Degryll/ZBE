#include "gtest/gtest.h"

#include <string>
#include <cstdint>

#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/JSON/resources/JSONImgDefLoader.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/factories/resources/SDLImgLoaderFtry.h"

namespace SDLImgLoaderFtryTest {

TEST(SDLImgLoaderFtryTest, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;

  auto& strStore = RsrcDictionary<std::string>::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();
  auto& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  auto& sdlImgLoaderRsrc = RsrcStore<SDLImgLoader>::getInstance();
  auto& rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();
  auto& rsrcDefLoaderRsrc = RsrcStore<RsrcDefLoader>::getInstance();
  auto& sdlWindowRsrc = RsrcStore<SDLWindow>::getInstance();
  auto& dict = NameRsrcDictionary::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["window"] = "testWindow";
  (*cfg)["imgdef"] = "testImgDef";
  (*cfg)["extension"] = ".png";

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  // Crear ventana
  auto win = std::make_shared<SDLWindow>();
  sdlWindowRsrc.insert("SDLWindow.testWindow", win);
  // Crear imgDef
  auto imgDefLoader = std::make_shared<JSONImgDefLoader>();
  rsrcDefLoaderRsrc.insert("RsrcDefLoader.testImgDef", imgDefLoader);

  SDLImgLoaderFtry sdlilf;
  sdlilf.create("SDLImgLoaderFtryTestName", cfgId);
  sdlilf.setup("SDLImgLoaderFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("SDLImgLoader.SDLImgLoaderFtryTestName");

  ASSERT_NE(0, outId) << "Must create a SDLImgLoader with given name";

  std::shared_ptr<SDLImgLoader> outImgLoader = sdlImgLoaderRsrc.get(outId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  strStore.clear();
  intStore.clear();
  configRsrc.clear();
  sdlImgLoaderRsrc.clear();
  rsrcLoaderRsrc.clear();
  rsrcDefLoaderRsrc.clear();
  sdlWindowRsrc.clear();
  dict.clear();

  zbe::SysError::clear();
}

}  // namespace SDLWindowFtryTest
