#include "gtest/gtest.h"

#include <string>
#include <cstdint>
#include <vector>

#include <GL/glew.h>

#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"

#include "ZBE/SDL/factories/drawers/OGLModelSheetDrawerFtry.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

namespace OGLModelSheetDrawerFtryTest {

TEST(OGLModelSheetDrawerFtry, Create) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  using namespace zbe;
  using namespace nlohmann;
  using namespace std::string_literals;
  auto& dict = NameRsrcDictionary::getInstance();
  auto& configRsrc = RsrcStore<json>::getInstance();
  auto& oGLMSDrawerRsrc = RsrcStore<OGLModelSheetDrawer<5, uint64_t, double, double, Vector3D, Vector3D> >::getInstance();
  auto& windowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  auto& drawerRsrc = RsrcStore<Behavior<uint64_t, double, double, Vector3D, Vector3D> >::getInstance();
  auto& intStore = RsrcDictionary<int64_t>::getInstance();

  std::vector<ShaderDef> shaderDefs;

  shaderDefs.push_back(ShaderDef("data/test/shaders/test_001.vs", GL_VERTEX_SHADER));
  shaderDefs.push_back(ShaderDef("data/test/shaders/test_001.fs", GL_FRAGMENT_SHADER));

  auto cfg = std::make_shared<json>();
  (*cfg)["window"] = "Ventanuco";
  (*cfg)["programId"] = "Pid";
  auto wd = std::make_shared<zbe::SDLOGLWindow>("Esto es una prueba!", 600, 400);

  uint64_t programId = wd->getShaderStore()->loadShader(shaderDefs);

  windowRsrc.insert("Ventanuco", wd);
  intStore.insert("Pid", programId);

  uint64_t cfgId = SysIdGenerator::getId();
  configRsrc.insert(cfgId, cfg);

  OGLModelSheetDrawerFtry<5, uint64_t, double, double, Vector3D, Vector3D> ssSDLdf;
  ssSDLdf.create("OGLModelSheetDrawerFtryTestName", cfgId);
  ssSDLdf.setup("OGLModelSheetDrawerFtryTestName", cfgId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no config errors.";

  uint64_t outId = dict.get("Drawer.OGLModelSheetDrawerFtryTestName");
  uint64_t swdId = dict.get("OGLMSDrawer.OGLModelSheetDrawerFtryTestName");

  ASSERT_NE(0, outId) << "Must create a Drawer with given name";
  ASSERT_NE(0, swdId) << "Must create a SpriteSheetSDLDrawer with given name";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors 1.";

  auto outDwr = drawerRsrc.get(outId);
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors 2.";

  auto outOMSDwr = oGLMSDrawerRsrc.get(swdId);

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Must be no store errors.";

  dict.clear();
  configRsrc.clear();
  oGLMSDrawerRsrc.clear();
  drawerRsrc.clear();
  windowRsrc.clear();

  zbe::SysError::clear();
}
}  // namespace OGLModelSheetDrawerFtryTest
