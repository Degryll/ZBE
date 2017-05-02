#include "gtest/gtest.h"

#include "ZBE/SDL/drawers/AnimatedSpriteSDLDrawer.h"

#include <cstdlib>
#include <ctime>

#include "ZBE/SDL/system/Window.h"
#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/archetypes/AnimatedDrawable.h"
#include "ZBE/entities/adaptors/AnimatedDrawableAnimatedSpriteAdaptor.h"

namespace AnimatedSpriteSDLDrawerTest {

static const int WINDOW_W = 100;
static const int WINDOW_H = 100;
static const int NSTATES = 4;
static const uint64_t NFRAMES[NSTATES] = {5, 6, 4, 3};
static const int64_t  WIDHTS[NSTATES] = {24, 20, 30, 40};
static const int64_t  HEIGHTS[NSTATES] = {15, 15, 15, 15};
static const int W = 120;
static const int H = 60;

class DrawerMock: public zbe::AnimatedDrawable,
                  public zbe::AvatarEntityAdapted<zbe::AnimatedSprite> {
public:
  DrawerMock() : x(0), y(0), w(0), h(0), g(0), s(0), f(0) {}

  void setX(int64_t x) {this->x = x;}
  void setY(int64_t y) {this->y = y;}
  void setW(int64_t w) {this->w = w;}
  void setH(int64_t h) {this->h = h;}
  void setG(uint64_t g) {this->g = g;}
  void setS(uint64_t s) {this->s = s;}
  void setF(uint64_t f) {this->f = f;}

  int64_t getX()    {return (x);}
  int64_t getY()    {return (y);}
  int64_t getW()    {return (w);}
  int64_t getH()    {return (h);}
  uint64_t getGraphics() {return (g);}
  double getDegrees() {return (0.0);}
  uint64_t getState() {return (s);}
  uint64_t getNumStates() {return (NSTATES);}
  uint64_t getFrame() {return (f);}
  uint64_t getNumFrames(uint64_t state) {return (NFRAMES[state]);}
  int64_t getGW(uint64_t state) {return (WIDHTS[state]);}
  int64_t getGH(uint64_t state) {return (HEIGHTS[state]);}
  const int64_t* getWArray() {return (WIDHTS);}
  const int64_t* getHArray() {return (HEIGHTS);}
  const uint64_t* getFArray() {return (NFRAMES);}

private:
  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;
  uint64_t g;
  uint64_t s;
  uint64_t f;
};

TEST(AnimatedSpriteSDLDrawer, DISABLED_Render) {
  srand(time(nullptr));
  zbe::Window window(WINDOW_W, WINDOW_H);

  zbe::AnimatedSpriteSDLDrawer drawer(&window);

  std::shared_ptr<DrawerMock> dm = std::make_shared<DrawerMock>();
  std::shared_ptr<zbe::Adaptor<zbe::AnimatedSprite> > spriteAdaptor = std::make_shared<zbe::AnimatedDrawableAnimatedSpriteAdaptor>(&(*dm));
  zbe::setAdaptor(dm,spriteAdaptor);

  char *m = new char[W*H*3];

  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W*NSTATES; j++) {
      for(int k = 0; k < 3; k++) {
        m[(i*W+j)*3+k] = rand() % 256;
      }
    }
  }

  uint64_t texture = window.loadImg(m, W, H, 24, W*3);

  delete[] m;

  char bgcolor[4] = {(char)(rand() % 256), (char)(rand() % 256), (char)(rand() % 256), 0x00};

  window.render2Texture();
  window.setBackgroundColor(bgcolor[0], bgcolor[1], bgcolor[2], bgcolor[3]);
  window.clear();

  int x = rand() % 50;
  int y = rand() % 50;
  int s = rand() % NSTATES;
  int f = rand() % NFRAMES[NSTATES];

  dm->setX(x);
  dm->setY(y);
  dm->setW(WIDHTS[s]);
  dm->setH(HEIGHTS[s]);
  dm->setG(texture);
  dm->setS(s);
  dm->setF(f);

  drawer.apply(dm);

  char *p = new char[WINDOW_W*WINDOW_H*4];
  window.readPixels(p, WINDOW_W*4);

  for(int i = 0; i < WINDOW_H; i++) {
    for(int j = 0; j < WINDOW_W; j++) {
      for(int k = 0; k < 4; k++) {
        if((j < x) || (j > (x+WIDHTS[s]))
        || (i < y) || (i > (y+HEIGHTS[s]))) {
          ASSERT_EQ(bgcolor[k], p[(i*WINDOW_W+j)*4+k]) << "Background pixel is equal to background color. I, j, k, w: " << i << ", " << j << ", " << k << ", " << WIDHTS[s] << ".";
        } else {
          // HEIGHTS[0] because all state has the same height.
          ASSERT_EQ(m[((s*HEIGHTS[0]+i-y)*W+(WIDHTS[s]*f+j-x))*4+k], p[(i*WINDOW_W+j)*4+k]) << "Foreground pixel is equal to random image. I, j, k, w: " << i << ", " << j << ", " << k << ", " << WIDHTS[s] << ".";
        }
      }
    }
  }

  delete[] p;
}

}  // namespace AnimatedSpriteSDLDrawerTest
