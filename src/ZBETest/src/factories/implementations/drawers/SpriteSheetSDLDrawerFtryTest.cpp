#include "gtest/gtest.h"

#include <string>
#include <cstdint>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/entities/avatars/SingleSprite.h"

#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"

#include "ZBE/SDL/factories/drawers/SpriteSheetSDLDrawerFtry.h"

namespace SpriteSheetSDLDrawerFtryTest {

TEST(SpriteSheetSDLDrawerFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto& dict = NameRsrcDictionary::getInstance();
  auto& configRsrc = RsrcStore<json>::getInstance();
  auto& sssDrawerRsrc = zbe::RsrcStore<zbe::SpriteSheetSDLDrawer<SingleSprite> >::getInstance();
  auto& windowRsrc = RsrcStore<zbe::SDLWindow>::getInstance();
  auto& drawerRsrc = RsrcStore<Behavior<SingleSprite> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["window"] = "Ventanuco";
  auto wd = std::make_shared<zbe::SDLWindow>("Esto es una prueba!", 600, 400);
  windowRsrc.insert("SDLWindow.Ventanuco", wd);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  SpriteSheetSDLDrawerFtry<SingleSprite> ssSDLdf;
  ssSDLdf.create("SpriteSheetSDLDrawerFtryTestName", cfgId);
  ssSDLdf.setup("SpriteSheetSDLDrawerFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Behavior.SpriteSheetSDLDrawerFtryTestName");
  uint64_t swdId = dict.get("SSSDLDrawer.SpriteSheetSDLDrawerFtryTestName");

  ASSERT_NE(0, outId) << "Must create a Drawer with given name";
  ASSERT_NE(0, swdId) << "Must create a SpriteSheetSDLDrawer with given name";

  auto outDwr = drawerRsrc.get(outId);
  auto outSSSDLWDwr = sssDrawerRsrc.get(swdId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  dict.clear();
  configRsrc.clear();
  sssDrawerRsrc.clear();
  drawerRsrc.clear();
  windowRsrc.clear();

  zbe::SysError::clear();
}
}  // namespace SpriteSheetSDLDrawerFtryTest
