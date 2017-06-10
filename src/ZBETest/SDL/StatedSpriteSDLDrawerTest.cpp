#include "gtest/gtest.h"

#include "ZBE/SDL/drawers/StatedSpriteSDLDrawer.h"

#include <cstdlib>
#include <ctime>

#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/core/tools/containers/ResourceManager.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/entities/AvatarEntity.h"

namespace StatedSpriteSDLDrawerTest {

static const int WINDOW_W = 100;
static const int WINDOW_H = 100;
static const int NSTATES = 4;

class DrawerMock: public zbe::AvatarEntityAdapted<zbe::StatedSprite> {
public:
  DrawerMock() : x(0), y(0), w(0), h(0), g(0), s(0) {}

  void setX(int64_t x) {this->x = x;}
  void setY(int64_t y) {this->y = y;}
  void setW(int64_t w) {this->w = w;}
  void setH(int64_t h) {this->h = h;}
  void setG(uint64_t g) {this->g = g;}
  void setS(uint64_t s) {this->s = s;}

  int64_t getX()    {return (x);}
  int64_t getY()    {return (y);}
  int64_t getW()    {return (w);}
  int64_t getH()    {return (h);}
  uint64_t getGraphics() {return (g);}
  double getDegrees() {return (0.0);}
  uint64_t getState() {return (s);}
  uint64_t getNumStates() {return (NSTATES);}

private:
  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;
  uint64_t g;
  uint64_t s;
};

TEST(StatedSpriteSDLDrawer, DISABLED_Render) {/*
  srand(time(nullptr));
  zbe::Window window(WINDOW_W, WINDOW_H);

  zbe::StatedSpriteSDLDrawer drawer(&window);

  std::shared_ptr<DrawerMock> dm = std::make_shared<DrawerMock>();
  std::shared_ptr<zbe::Adaptor<zbe::StatedSprite> > spriteAdaptor = std::make_shared<zbe::StatedDrawableStatedSpriteAdaptor>(&(*dm));
  zbe::setAdaptor(dm,spriteAdaptor);

  int w = rand() % 20 + 20;
  int h = rand() % 20 + 20;

  const int IMG_W = w*NSTATES;

  char *m = new char[IMG_W*h*3];

  for(int i = 0; i < h; i++) {
    for(int j = 0; j < IMG_W; j++) {
      for(int k = 0; k < 3; k++) {
        m[(i*IMG_W+j)*3+k] = rand() % 256;
      }
    }
  }

  uint64_t texture = window.loadImg(m, w*NSTATES, h, 24, IMG_W*3);

  delete[] m;

  char bgcolor[4] = {(char)(rand() % 256), (char)(rand() % 256), (char)(rand() % 256), 0x00};

  window.render2Texture();
  window.setBackgroundColor(bgcolor[0], bgcolor[1], bgcolor[2], bgcolor[3]);
  window.clear();

  int x = rand() % 50;
  int y = rand() % 50;
  int s = rand() % NSTATES;

  dm->setX(x);
  dm->setY(y);
  dm->setW(w);
  dm->setH(h);
  dm->setG(texture);
  dm->setS(s);

  drawer.apply(dm);

  char *p = new char[WINDOW_W*WINDOW_H*4];

  window.readPixels(p, w*4);

  for(int i = 0; i < WINDOW_H; i++) {
    for(int j = 0; j < WINDOW_W; j++) {
      for(int k = 0; k < 4; k++) {
        if((j < x) || (j > (x+w))
        || (i < y) || (i > (y+h))) {
          ASSERT_EQ(bgcolor[k], p[(i*WINDOW_W+j)*4+k]) << "Background pixel is equal to background color. I, j, k, w: " << i << ", " << j << ", " << k << ", " << w << ".";
        } else {
          ASSERT_EQ(m[((i-y)*IMG_W+(w*s+j-x))*4+k], p[(i*WINDOW_W+j)*4+k]) << "Foreground pixel is equal to random image. I, j, k, w: " << i << ", " << j << ", " << k << ", " << w << ".";
        }
      }
    }
  }

  delete[] p;*/
}

}  // namespace StatedSpriteSDLDrawerTest
