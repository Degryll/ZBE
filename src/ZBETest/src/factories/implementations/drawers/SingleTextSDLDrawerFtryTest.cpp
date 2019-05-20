#include "gtest/gtest.h"

#include <string>
#include <cstdint>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"

#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"

#include "ZBE/SDL/factories/drawers/SingleTextSDLDrawerFtry.h"

namespace SingleTextSDLDrawerFtryTest {
//obj\Release\src\ZBETest\src\factories\implementations\drawers\SingleTextSDLDrawerFtryTest.o:SingleTextSDLDrawerFtryTest.cpp|| undefined reference to `zbe::SingleTextSDLDrawerFtry::create(std::string, unsigned long long)'|
TEST(SingleTextSDLDrawerFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto& dict = NameRsrcDictionary::getInstance();
  auto& configRsrc = RsrcStore<json>::getInstance();
  auto& STSDrawerRsrc = zbe::RsrcStore<zbe::SingleTextSDLDrawer>::getInstance();
  auto& windowRsrc = RsrcStore<zbe::SDLWindow>::getInstance();
  auto& drawerRsrc = RsrcStore<Behavior<SingleTextSprite> >::getInstance();

  auto cfg = std::make_shared<json>();
  (*cfg)["window"] = "Ventanuco";
  auto wd = std::make_shared<zbe::SDLWindow>("Esto es una prueba!", 600, 400);
  windowRsrc.insert("Ventanuco", wd);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  zbe::SingleTextSDLDrawerFtry STSDLdf;
  STSDLdf.create("SingleTextSDLDrawerFtryTestName", cfgId);
  STSDLdf.setup("SingleTextSDLDrawerFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Drawer.SingleTextSDLDrawerFtryTestName");
  uint64_t swdId = dict.get("STSDLDrawer.SingleTextSDLDrawerFtryTestName");

  ASSERT_NE(0, outId) << "Must create a Drawer with given name";
  ASSERT_NE(0, swdId) << "Must create a SingleTextSDLDrawer with given name";

  auto outDwr = drawerRsrc.get(outId);
  auto outSTSDLWDwr = STSDrawerRsrc.get(swdId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  dict.clear();
  configRsrc.clear();
  STSDrawerRsrc.clear();
  drawerRsrc.clear();
  windowRsrc.clear();

  zbe::SysError::clear();
}
}  // namespace SingleTextSDLDrawerFtryTest
