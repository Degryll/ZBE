#include "gtest/gtest.h"

#include <string>
#include <cstdint>

#include "ZBE/resources/loaders/RsrcDefLoader.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/system/system.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/resources/SDLImgLoader.h"

namespace SDLImgLoaderTest {

class DummyRsrcDefLoader : public zbe::RsrcDefLoader {
public:

  DummyRsrcDefLoader() : imgId(0) {}

  void loadRsrcDef(const std::filesystem::path&, uint64_t rsrcId) {
    imgId = rsrcId;
  }

  const std::filesystem::path getExtension() {
    return ".test";
  }

  uint64_t imgId;
};

TEST(SDLImgLoaderFtryTest, Create) {
  using namespace zbe;

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  auto win = std::make_shared<zbe::SDLWindow>("test", 100, 100);
  auto defLoader = std::make_shared<DummyRsrcDefLoader>();

  SDLImgLoader sdlilf;
  sdlilf.setImgStore(win->getImgStore());
  sdlilf.setImgDefLoader(defLoader);

  EXPECT_EQ(0, defLoader->imgId) << "Definition loader must not be called.";

  sdlilf.load("data/test/img/testing_001.png");

  EXPECT_NE(0, defLoader->imgId) << "Definition loader must be called.";

  zbe::SysError::clear();
}

}  // namespace SDLImgLoaderTest
