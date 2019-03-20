#include "gtest/gtest.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/SDL/daemons/SDLOGLWindowDaemon.h"

namespace SDLOGLWindowDaemonTest {

TEST(SDLOGLWindowDaemon, Run) {
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initially no errors.";

  auto& windowRsrc = zbe::RsrcStore<zbe::SDLOGLWindow>::getInstance();

  zbe::SDLOGLWindowDaemon dmn;

  dmn.setName("dummy.oglwindow");
  dmn.setTitle("title");
  dmn.setX(0);
  dmn.setY(0);
  dmn.setWidth(640);
  dmn.setHeight(480);
  dmn.setWindowFlags(0);
  dmn.setRendererFlags(0);

  std::shared_ptr<zbe::SDLOGLWindow> noWindow = windowRsrc.get("dummy.oglwindow");

  EXPECT_EQ(2, zbe::SysError::getNErrors()) << "The Window is not created yet.";
  zbe::SysError::clear();

  dmn.run();

  std::shared_ptr<zbe::SDLOGLWindow> window = windowRsrc.get("dummy.oglwindow");

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "The Window should be created.";

  zbe::SysError::clear();
}

}  // namespace SDLOGLWindowDaemonTest
