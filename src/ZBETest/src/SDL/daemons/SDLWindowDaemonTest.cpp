#include "gtest/gtest.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/daemons/SDLWindowDaemon.h"

namespace SDLWindowDaemonTest {

TEST(SDLWindowDaemon, Run) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  auto& windowRsrc = zbe::RsrcStore<zbe::SDLWindow>::getInstance();

  zbe::SDLWindowDaemon dmn;

  dmn.setName("dummy.window");
  dmn.setTitle("title");
  dmn.setX(0);
  dmn.setY(0);
  dmn.setWidth(640);
  dmn.setHeight(480);
  dmn.setWindowFlags(0);
  dmn.setRendererFlags(0);

  std::shared_ptr<zbe::SDLWindow> noWindow = windowRsrc.get("dummy.window");

  EXPECT_EQ(2, zbe::SysError::getNErrors()) << "The Window is not created yet.";
  zbe::SysError::clear();

  dmn.run();

  std::shared_ptr<zbe::SDLWindow> window = windowRsrc.get("dummy.window");

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "The Window should be created.";

  zbe::SysError::clear();
}

}  // namespace SDLWindowDaemonTest
