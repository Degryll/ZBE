#include "gtest/gtest.h"

#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"

#include <cstdlib>
#include <ctime>

#include "ZBE/SDL/system/Window.h"
#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/archetypes/Drawable.h"
#include "ZBE/entities/adaptors/SimpleDrawableSingleSpriteAdaptor.h"

namespace SingleSpriteSDLDrawerTest {

static const int WINDOW_W = 10;
static const int WINDOW_H = 10;

class DrawerMock: public zbe::Drawable,
                  public zbe::AvatarEntityAdapted<zbe::SingleSprite> {
public:
  DrawerMock() : x(0), y(0), w(0), h(0), g(0) {}

  void setX(int64_t x) {this->x = x;}
  void setY(int64_t y) {this->y = y;}
  void setW(int64_t w) {this->w = w;}
  void setH(int64_t h) {this->h = h;}
  void setG(uint64_t g) {this->g = g;}

  int64_t getX()    {return (x);}
  int64_t getY()    {return (y);}
  int64_t getW()    {return (w);}
  int64_t getH()    {return (h);}
  uint64_t getGraphics() {return (g);}

private:
  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;
  uint64_t g;
};

TEST(SingleSpriteSDLDrawer, DISABLED_Render) {
  //srand(time(nullptr));
  zbe::Window window(WINDOW_W, WINDOW_H);

  zbe::SingleSpriteSDLDrawer drawer(&window);

  std::shared_ptr<DrawerMock> dm = std::make_shared<DrawerMock>();
  std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(&(*dm));
  zbe::setAdaptor(dm,spriteAdaptor);

  int w = rand() % 20 + 20;
  int h = rand() % 20 + 20;

  char *m = new char[w*h*3];

  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      for(int k = 0; k < 4; k++) {
        if (k == 3) {
          m[(i*w+j)*3+k] = 0x00;
        } else {
          m[(i*w+j)*3+k] = rand() % 256;
        }
      }
    }
  }

  uint64_t texture = window.loadImg(m, w, h, 32, w*4);

  delete[] m;

  char bgcolor[4] = {(char)(rand() % 256), (char)(rand() % 256), (char)(rand() % 256), 0x00};

printf("bgcolor: %hhd, %hhd, %hhd, %hhd\n", bgcolor[0], bgcolor[1], bgcolor[2], bgcolor[3]);

  window.render2Texture();
  window.setBackgroundColor(bgcolor[0], bgcolor[1], bgcolor[2], bgcolor[3]);
  window.clear();

  int x = rand() % 50;
  int y = rand() % 50;

printf("IMG: x: %d, y: %d, w: %d, h: %d\n", x, y, w, h);

  dm->setX(x);
  dm->setY(y);
  dm->setW(w);
  dm->setH(h);
  dm->setG(texture);

  drawer.apply(dm);

  char *p = new char[WINDOW_W*WINDOW_H*4];

  memset(p, 42, WINDOW_W*WINDOW_H*4);

printf("PRE %p\n", p);fflush(stdout);
  //window.readPixels(p, 1);
printf("POS %p\n", p);fflush(stdout);

  for(int i = 0; i < WINDOW_H; i++) {
    for(int j = 0; j < WINDOW_W; j++) {
      for(int k = 0; k < 4; k++) {
        if((j < x) || (j > (x+w))
        || (i < y) || (i > (y+h))) {
          printf("PQUE!! i: %d, j: %d, k: %d\n", i, j, k);fflush(stdout);
          if((i == 22) && (j > 5)) {
            printf("p[%d]: %hhd(%d, %d)\n", (i*WINDOW_W+j)*4+k, p[(i*WINDOW_W+j)*4+k], i, j);fflush(stdout);
          }
          printf("ASSERT i: %d, j: %d, k: %d -> pos: %d, val: %hhd\n", i, j, k, (i*WINDOW_W+j)*4+k, p[(i*WINDOW_W+j)*4+k]);fflush(stdout);
          //ASSERT_EQ(bgcolor[k], p[(i*WINDOW_W+j)*4+k]) << "Background pixel is equal to background color. I, j, k, w: " << i << ", " << j << ", " << k << ", " << w << ".";
        } else {
          //ASSERT_EQ(m[((i-y)*w+(j-x))*4+k], p[(i*WINDOW_W+j)*4+k]) << "Foreground pixel is equal to random image. I, j, k, w: " << i << ", " << j << ", " << k << ", " << w << ".";
        }
      }
    }
  }
printf("PQUE!! \n");fflush(stdout);
  delete[] p;
}

}  // namespace SingleSpriteSDLDrawerTest
