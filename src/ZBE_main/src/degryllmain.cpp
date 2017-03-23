#include "degryllmain.h"

#include <cstdio>

#include "ZBE/archetypes/Drawable.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/entities/adaptors/SimpleSpriteAdaptor.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/SDL/system/Window.h"
#include "ZBE/SDL/drawers/SimpleSpriteSDLDrawer.h"
#include "ZBE/core/daemons/DaemonMaster.h"


#include "game/events/handlers/ExitInputHandler.h"

class GameReactor {};

namespace zbe {

//class Block: public zbe::Drawable,
//             public zbe::SimpleSpriteEntityAdapted<zbe::Drawable> {
//public:
//  Block() : SimpleSpriteEntityAdapted(this), x(0), y(0), t(0), lm(ListManager<TicketedForwardList<SimpleSpriteEntity*> >::getInstance()), ticket(nullptr) {}
//  Block(int64_t x, int64_t y, uint64_t t, uint64_t id) : SimpleSpriteEntityAdapted(this), x(x), y(y), t(t), lm(ListManager<TicketedForwardList<SimpleSpriteEntity*> >::getInstance()), ticket(lm.get(id)->push_front(this)) {}
//
//  void addTo(uint64_t id) {
//    ticket = lm.get(id)->push_front(this);
//  }
//
//  void setX(int64_t x) {this->x = x;}
//  void setY(int64_t y) {this->y = y;}
//  void setXY(int64_t x, int64_t y) {this->x = x; this->y = y;}
//  void setType(int64_t type) {this->t = type;}
//
//  int64_t getX() {return (x);}
//  int64_t getY() {return (y);}
//  int64_t getW() {return (1);}
//  int64_t getH() {return (1);}
//  uint64_t getGraphics() {return (t);}
//
//  void setVisible()   {ticket->setACTIVE();}    //!< The block will be visible.
//  void setInvisible() {ticket->setINACTIVE();}  //!< The block will be invisible.
//  void setERASED()    {ticket->setERASED();}    //!< The block won't be used anymore.
//
//private:
//  int64_t x;
//  int64_t y;
//  uint64_t t;
//  ListManager<TicketedForwardList<SimpleSpriteEntity*> >& lm;
//  std::shared_ptr< TicketedElement<SimpleSpriteEntity*> > ticket;
//};
//
//class SimpleDrawableBoardSpriteAdaptor : public SimpleSpriteAdaptor<Drawable> {
//public:
//  SimpleDrawableBoardSpriteAdaptor(int topLeftX, int topLeftY, int tileW, int tileH) : x(topLeftX), y(topLeftY), w(tileW), h(tileH) {}
//
//  std::shared_ptr<SimpleSprite> getSimpleSprite(Drawable* entity) {
//    std::shared_ptr<SimpleSprite> s = std::make_shared<SimpleSprite>();
//
//    s->x = entity->getX() * w + x;
//    s->y = entity->getY() * w + y;
//    s->w = w;
//    s->h = h;
//    s->graphics = entity->getGraphics();
//
//    return (s);
//  }
//
//private:
//  int64_t x;
//  int64_t y;
//  int64_t w;
//  int64_t h;
//};
//
//class Board {
//public:
//  Board(uint64_t width, uint64_t height, uint64_t t, uint64_t id, SimpleSpriteAdaptor<zbe::Drawable> *ssa) : w(width), h(height), b(new int[w*h]), bb(new Block[w*h]()) {
//    for(uint64_t i = 0; i < height; i++) {
//      for(uint64_t j = 0; j < width; j++) {
//        b[i*width+j] = 0;
//        bb[i*width+j].addTo(id);
//        bb[i*width+j].setX(j);
//        bb[i*width+j].setY(i);
//        bb[i*width+j].setType(t);
//        bb[i*width+j].setInvisible();
//        bb[i*width+j].setSimpleSpriteAdaptor(ssa);
//      }
//    }
//  }
//
//  void setValue(uint64_t x, uint64_t y, uint64_t t) {
//    b[y*w+x] = t;
//    if(t) bb[y*w+x].setVisible();
//    else bb[y*w+x].setInvisible();
//  }
//
//  void setTile(uint64_t x, uint64_t y, uint64_t t) {
//    setValue(x, y, t);
//
//    check();
//  }
//
//  bool isOcupied(int x, int y) {
//    if((x < 0) || (x >= w) || (y < 0) || (y >= h)) return (true);
//
//    return (b[y*w+x]);
//  }
//
//  void occupy(int x, int y) {
//    if((x < 0) || (x >= w) || (y < 0) || (y >= h)) return;
//
//    setTile(x, y, 1);
//  }
//
//  bool check() {
//    for(int i = h-1; i >= 0; i--) {
//        int o = 0;
//      for(int j = 0; j < w; j++) {
//        o += b[i*w+j];
//      }
//      if (o == w) {
//        for(int k = i; k > 0; k--) {
//          for(int l = 0; l < w; l++) {
//            setValue(l, k, b[(k-1)*w+l]);
//          }
//        }
//        for(int l = 0; l < w; l++) {
//          b[l] = 0;
//        }
//      }
//    }
//  }
//
//private:
//  uint64_t w;
//  uint64_t h;
//  int *b;
//  Block* bb;
//};
//
//class Tetromino {
//public:
//  enum TetrominoType {
//    PALO     = 1,
//    CUADRADO = 2,
//    Z        = 3,
//    S        = 4,
//    T        = 5,
//    L        = 6,
//    Linv     = 7
//  };
//
//  Tetromino(uint64_t img, uint64_t id, SimpleSpriteAdaptor<zbe::Drawable> *ssa, Board& board, int type = 0) : b(), x(5), y(3), t(type), r(0), board(board) {
//    for(uint64_t i = 0; i < 4; i++) {
//      b[i].addTo(id);
//      //b[i].setType(type);
//      b[i].setSimpleSpriteAdaptor(ssa);
//      b[i].setType(img);
//
//      if(t) b[i].setVisible();
//      else b[i].setInvisible();
//    }
//
//    setType(type);
//  }
//
//  void setType(int type, int rotation = 0) {
//    if(!isOcupied(x, y, type, rotation)) {
//      this->t = type;
//      this->r = rotation;
//      setPosition();
//    }
////    this->t = type;
////    this->r = rotation;
////    setPosition();
////    switch (type) {
////    case PALO:     setPalo(); break;
////    case CUADRADO: setCuadrado(); break;
////    case Z:        setZ(); break;
////    case S:        setS(); break;
////    case T:        setT(); break;
////    case L:        setL(); break;
////    case Linv:     setLinv(); break;
////    default:       setInvisible();
////    }
//  }
//
//  void rotateLeft()  {
//    int newr = (r+1) % 4;
//    if(!isOcupied(x, y, t, newr)) {
//      r = newr;
//      setPosition();
//    }
//  }
//  //void rotateLeft()  {setType(t, (r+1)%4);}
//  //void rotateRight() {setType(t, (r-1)%4);}
//
//  void drop() {
//    if(!isOcupied(x, y+1, t, r)) {
//      y++;
//      setPosition();
//    } else {
//      occupy(x, y, t, r);
//      x = 5;
//      y = 3;
//      //t = (t+1) % 8;
//      t = (rand() % 7) + 1;
//      setPosition();
//    }
//  }
//
//  void move(int offset) {
//    if(!isOcupied(x+offset, y, t, r)) {
//      x += offset,
//      setPosition();
//    }
//  }
//
//private:
//
//  void setPosition() {
//    for(uint64_t i = 0; i < 4; i++) {
//      if (t) {
//        b[i].setVisible();
//        b[i].setXY(x+offsets[t-1][r][i][0], y+offsets[t-1][r][i][1]);
//      } else {
//        b[i].setInvisible();
//      }
//    }
//  }
//
//  bool isOcupied(int x, int y, int type, int rotation) {
//    return ( board.isOcupied(x+offsets[type-1][rotation][0][0], y+offsets[type-1][rotation][0][1])
//          || board.isOcupied(x+offsets[type-1][rotation][1][0], y+offsets[type-1][rotation][1][1])
//          || board.isOcupied(x+offsets[type-1][rotation][2][0], y+offsets[type-1][rotation][2][1])
//          || board.isOcupied(x+offsets[type-1][rotation][3][0], y+offsets[type-1][rotation][3][1]));
//  }
//
//  void occupy(int x, int y, int type, int rotation) {
//    board.occupy(x+offsets[type-1][rotation][0][0], y+offsets[type-1][rotation][0][1]);
//    board.occupy(x+offsets[type-1][rotation][1][0], y+offsets[type-1][rotation][1][1]);
//    board.occupy(x+offsets[type-1][rotation][2][0], y+offsets[type-1][rotation][2][1]);
//    board.occupy(x+offsets[type-1][rotation][3][0], y+offsets[type-1][rotation][3][1]);
//  }
//
//  void setPalo() {
//    if(r %2) {
//      b[0].setVisible();
//      b[0].setXY(x-2, y);
//      b[1].setVisible();
//      b[1].setXY(x-1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x+1, y);
//    } else {  // rotate
//      b[0].setVisible();
//      b[0].setXY(x, y-2);
//      b[1].setVisible();
//      b[1].setXY(x, y-1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y+1);
//    }
//  }
//
//  void setCuadrado() {
//    b[0].setVisible();
//    b[0].setXY(x, y-1);
//    b[1].setVisible();
//    b[1].setXY(x+1, y-1);
//    b[2].setVisible();
//    b[2].setXY(x, y);
//    b[3].setVisible();
//    b[3].setXY(x+1, y);
//  }
//
//  void setZ() {
//    if(r %2) {
//      b[0].setVisible();
//      b[0].setXY(x, y-1);
//      b[1].setVisible();
//      b[1].setXY(x-1, y-1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x+1, y);
//    } else {
//      b[0].setVisible();
//      b[0].setXY(x+1, y-1);
//      b[1].setVisible();
//      b[1].setXY(x+1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y+1);
//    }
//  }
//
//  void setS() {
//    if(r %2) {
//      b[0].setVisible();
//      b[0].setXY(x, y-1);
//      b[1].setVisible();
//      b[1].setXY(x+1, y-1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x-1, y);
//    } else {
//      b[0].setVisible();
//      b[0].setXY(x-1, y-1);
//      b[1].setVisible();
//      b[1].setXY(x-1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y+1);
//    }
//  }
//
//  void setT() {
//    switch (r) {
//    case 0:
//      b[0].setVisible();
//      b[0].setXY(x, y-1);
//      b[1].setVisible();
//      b[1].setXY(x-1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x+1, y);
//      break;
//    case 1:
//      b[0].setVisible();
//      b[0].setXY(x-1, y);
//      b[1].setVisible();
//      b[1].setXY(x, y+1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y-1);
//      break;
//    case 2:
//      b[0].setVisible();
//      b[0].setXY(x, y+1);
//      b[1].setVisible();
//      b[1].setXY(x-1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x+1, y);
//      break;
//    case 3:
//      b[0].setVisible();
//      b[0].setXY(x+1, y);
//      b[1].setVisible();
//      b[1].setXY(x, y-1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y+1);
//      break;
//    }
//  }
//
//  void setL() {
//    switch (r) {
//    case 0:
//      b[0].setVisible();
//      b[0].setXY(x, y-2);
//      b[1].setVisible();
//      b[1].setXY(x, y-1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x+1, y);
//      break;
//    case 1:
//      b[0].setVisible();
//      b[0].setXY(x-2, y);
//      b[1].setVisible();
//      b[1].setXY(x-1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y-1);
//      break;
//    case 2:
//      b[0].setVisible();
//      b[0].setXY(x, y+2);
//      b[1].setVisible();
//      b[1].setXY(x, y+1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x-1, y);
//      break;
//    case 3:
//      b[0].setVisible();
//      b[0].setXY(x+2, y);
//      b[1].setVisible();
//      b[1].setXY(x+1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y+1);
//      break;
//    }
//  }
//
//  void setLinv() {
//    switch (r) {
//    case 0:
//      b[0].setVisible();
//      b[0].setXY(x, y-2);
//      b[1].setVisible();
//      b[1].setXY(x, y-1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x-1, y);
//      break;
//    case 1:
//      b[0].setVisible();
//      b[0].setXY(x-2, y);
//      b[1].setVisible();
//      b[1].setXY(x-1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y+1);
//      break;
//    case 2:
//      b[0].setVisible();
//      b[0].setXY(x, y+2);
//      b[1].setVisible();
//      b[1].setXY(x, y+1);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x+1, y);
//      break;
//    case 3:
//      b[0].setVisible();
//      b[0].setXY(x+2, y);
//      b[1].setVisible();
//      b[1].setXY(x+1, y);
//      b[2].setVisible();
//      b[2].setXY(x, y);
//      b[3].setVisible();
//      b[3].setXY(x, y-1);
//      break;
//    }
//  }
//
//  void setInvisible() {
//    for(uint64_t i = 0; i < 4; i++) {
//      b[i].setInvisible();
//    }
//  }
//
//  static int offsets[7][4][4][2];
//  Block b[4];
//  int x, y;
//  int t;
//  int r;
//  Board& board;
//};
//
//int Tetromino::offsets[7][4][4][2] = {{ {{ -2,  0 }, { -1,  0 }, {  0,  0 }, { +1,  0 }}, {{  0, -2 }, {  0, -1 }, {  0,  0 }, {  0, +1 }}, {{ -2,  0 }, { -1,  0 }, {  0,  0 }, { +1,  0 }}, {{  0, -2 }, {  0, -1 }, {  0,  0 }, {  0, +1 }} },
//                                      { {{  0, -1 }, { +1, -1 }, {  0,  0 }, { +1,  0 }}, {{  0, -1 }, { +1, -1 }, {  0,  0 }, { +1,  0 }}, {{  0, -1 }, { +1, -1 }, {  0,  0 }, { +1,  0 }}, {{  0, -1 }, { +1, -1 }, {  0,  0 }, { +1,  0 }} },
//                                      { {{  0, -1 }, { -1, -1 }, {  0,  0 }, { +1,  0 }}, {{ +1, -1 }, { +1,  0 }, {  0,  0 }, {  0, +1 }}, {{  0, -1 }, { -1, -1 }, {  0,  0 }, { +1,  0 }}, {{ +1, -1 }, { +1,  0 }, {  0,  0 }, {  0, +1 }} },
//                                      { {{  0, -1 }, { +1, -1 }, {  0,  0 }, { -1,  0 }}, {{ -1, -1 }, { -1,  0 }, {  0,  0 }, {  0, +1 }}, {{  0, -1 }, { +1, -1 }, {  0,  0 }, { -1,  0 }}, {{ -1, -1 }, { -1,  0 }, {  0,  0 }, {  0, +1 }} },
//                                      { {{  0, -1 }, { -1,  0 }, {  0,  0 }, { +1,  0 }}, {{ -1,  0 }, {  0, +1 }, {  0,  0 }, {  0, -1 }}, {{  0, +1 }, { -1,  0 }, {  0,  0 }, { +1,  0 }}, {{ +1,  0 }, {  0, -1 }, {  0,  0 }, {  0, +1 }} },
//                                      { {{  0, -2 }, {  0, -1 }, {  0,  0 }, { +1,  0 }}, {{ -2,  0 }, { -1,  0 }, {  0,  0 }, {  0, -1 }}, {{  0, +2 }, {  0, +1 }, {  0,  0 }, { -1,  0 }}, {{ +2,  0 }, { +1,  0 }, {  0,  0 }, {  0, +1 }} },
//                                      { {{  0, -2 }, {  0, -1 }, {  0,  0 }, { -1,  0 }}, {{ -2,  0 }, { -1,  0 }, {  0,  0 }, {  0, +1 }}, {{  0, +2 }, {  0, +1 }, {  0,  0 }, { +1,  0 }}, {{ +2,  0 }, { +1,  0 }, {  0,  0 }, {  0, -1 }} }};
//
//class MoveLeftInputHandler : public zbe::InputHandler {
//	public:
//	  MoveLeftInputHandler(const MoveLeftInputHandler&) = delete;
//	  void operator=(const MoveLeftInputHandler&) = delete;
//
//  	MoveLeftInputHandler(Tetromino& tetromino) : t(tetromino) {}
//
//  	void run(float status) {
//      if( status) {
//          t.move(-1);
//      }
//  	}
//
//	private:
//    Tetromino& t;
//};
//
//class MoveRightInputHandler : public zbe::InputHandler {
//	public:
//	  MoveRightInputHandler(const MoveRightInputHandler&) = delete;
//	  void operator=(const MoveRightInputHandler&) = delete;
//
//  	MoveRightInputHandler(Tetromino& tetromino) : t(tetromino) {}
//
//  	void run(float status) {
//      if( status) {
//          t.move(+1);
//      }
//  	}
//
//	private:
//    Tetromino& t;
//};
//
//class RotateLeftInputHandler : public zbe::InputHandler {
//	public:
//	  RotateLeftInputHandler(const RotateLeftInputHandler&) = delete;
//	  void operator=(const RotateLeftInputHandler&) = delete;
//
//  	RotateLeftInputHandler(Tetromino& tetromino) : t(tetromino) {}
//
//  	void run(float status) {
//      if( status) {
//          t.rotateLeft();
//      }
//  	}
//
//	private:
//    Tetromino& t;
//};
//
}  // namespace zbe


// Crear Handler de teclado para voler el tetronimo de izq a derecha
// handler tiene acceso a un oraculo para saber los limites del mata. el oraculo puede ser el mapa mismo

int degryllmain(int, char**) {
//  printf("--- Degryll main ---\n\n");
//
//  srand(time(nullptr));
//
//    enum {
//    INPUTEVENT = 0,
//    COLLISIONEVENT = 1,
//    TIMEEVENT = 2,
//
//    DRAWLIST = 1,
//
//    COLLISIONATORLIST = 1,
////    MOBILELIST = 1,
////    BALLACTUATORLIST = 1,
////    COLLISIONABLELIST = 1,
////    BOARDACTUATORLIST = 1,
////    BRICKACTUATORLIST = 2,
//
//    WIDTH = 1024,
//    HEIGHT = 768
//  };
//
//  const char blockfilename[] = "data/images/batis/bloque_32.png";
//  uint64_t blockgraphics;
//
//
//  zbe::EventStore& store = zbe::EventStore::getInstance();
//
//  zbe::SDLEventDispatcher & sdlEventDist = zbe::SDLEventDispatcher::getInstance();
//  zbe::InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
//  zbe::InputEventGenerator ieg(inputBuffer,INPUTEVENT);
//
//  zbe::TicketedForwardList<zbe::CollisionatorEntity<GameReactor>*> ctl;
//  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<GameReactor>*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<GameReactor>*> >::getInstance();
//  lmct.insert(COLLISIONATORLIST, &ctl);
//  zbe::CollisionEventGenerator<GameReactor> ceg(COLLISIONATORLIST, COLLISIONEVENT);
//
//  zbe::TimeEventGenerator teg(TIMEEVENT);
//
//  zbe::Timer *sysTimer = new zbe::SDLTimer(true);
//  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
//  sysTime.setSystemTimer(sysTimer);
//
//  zbe::Window window(WIDTH,HEIGHT);
//  blockgraphics = window.loadImg(blockfilename);
//
//  zbe::SimpleSpriteSDLDrawer drawer(&window);
//
//  zbe::DaemonMaster dMaster;
////  std::vector<zbe::Mobile<2>*> vmobile;
////  zbe::ListManager< std::vector<zbe::Mobile<2>*> >& lmmobile = zbe::ListManager< std::vector<zbe::Mobile<2>*> >::getInstance();
////  lmmobile.insert(MOBILELIST, &vmobile);
////  std::shared_ptr<zbe::Daemon> bball(new  zbe::BehaviorDaemon< zbe::Mobile<2>, std::vector<zbe::Mobile<2>*> >(new zbe::UniformLinearMotion<2>(), MOBILELIST));
////  dMaster.addDaemon(bball);
//
//  zbe::SimpleDrawableBoardSpriteAdaptor blockAdaptor(100, 100, 32, 32);
//
//  zbe::TicketedForwardList<zbe::SimpleSpriteEntity*> sprites;
//  zbe::ListManager< zbe::TicketedForwardList<zbe::SimpleSpriteEntity*> >& lmdraw = zbe::ListManager< zbe::TicketedForwardList<zbe::SimpleSpriteEntity*> >::getInstance();
//  lmdraw.insert(DRAWLIST, &sprites);
//
////  zbe::Block block(0, 0, blockgraphics, DRAWLIST);
////  block.setSimpleSpriteAdaptor(&blockAdaptor);
////
////  zbe::Block blockInv(0, 1, blockgraphics, DRAWLIST);
////  blockInv.setSimpleSpriteAdaptor(&blockAdaptor);
//
//  zbe::Board board(10, 20, blockgraphics, DRAWLIST, &blockAdaptor);
//
//  zbe::Tetromino tetromino(blockgraphics, DRAWLIST, &blockAdaptor, board, 1);
////  //ball
////  std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >*> ballActuatorsList;
////  zbe::ListManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >* > >& lmBallActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >* > >::getInstance();
////  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
////  game::GameBallBouncer gbBouncer;
////  ballActuatorsList.push_front(&gbBouncer);
////
////  zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> collisionablesList;
////  zbe::ListManager<zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >& lmCollisionablesList = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >::getInstance();
////  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);
//
//
////  zbe::SimpleSpriteAdaptor<zbe::Drawable>* spriteAdaptor = new zbe::SimpleDrawableSimpleSpriteAdaptor();
////  zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2> * movableCatorAdaptor = new zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2>();
//
//  game::ExitInputHandler terminator;
//  ieg.addHandler(zbe::ZBEK_ESCAPE, &terminator);
//
//  zbe::MoveLeftInputHandler moveleft(tetromino);
//  ieg.addHandler(zbe::ZBEK_a, &moveleft);
//
//  zbe::MoveRightInputHandler moveright(tetromino);
//  ieg.addHandler(zbe::ZBEK_d, &moveright);
//
//  zbe::RotateLeftInputHandler rleft(tetromino);
//  ieg.addHandler(zbe::ZBEK_SPACE, &rleft);
////  for(int i = 0; i<1000 ; i++){
////      //game::GameBall* ball = new game::GameBall(98.623993, 85.728439, 16 , -100, -100, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
////      game::GameBall* ball = new game::GameBall((rand()%200 + 400), (rand()%200 + 400), 16 , (rand()%200 - 100), (rand()%200 - 100), BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
////      ctl.push_front(ball);
////      ball->setSimpleSpriteAdaptor(spriteAdaptor);
////      ball->setMovableCollisionatorAdaptor(movableCatorAdaptor);
////      vmobile.push_back(ball);
////      sprites.push_front(ball);
////  }
//
//  //bricks
////  zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >& lmSimpleConerActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >::getInstance();
////  std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> brickActuatorsList;
////  lmSimpleConerActuatorsList.insert(BRICKACTUATORLIST, &brickActuatorsList);
////  for(int i = 0; i<8 ; i++){
////      for(int j = 0; j<8 ; j++){
////          game::GameBlock *brick = new game::GameBlock(i*51+ 100, j*32 + 100, 51, 32, brickgraphics, BRICKACTUATORLIST);
////          brick->setSimpleSpriteAdaptor(spriteAdaptor);
////          collisionablesList.push_front(brick);
////          sprites.push_front(brick);
////      }
////  }
//
//  //board
////  std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> boardActuatorsList;
////  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, &boardActuatorsList);
////  game::GameBoard board(WIDTH, HEIGHT, BOARDACTUATORLIST);
////  collisionablesList.push_front(&board);
//
//  sysTimer->start();
//  sdlEventDist.run();
//  sysTime.update();
//
//  int64_t endT = sysTime.getTotalTime();// instant at which the frame ends
//  int64_t initT = 0;//Lets start
//
//  int64_t maxFrameTime = zbe::SECOND / 64;
//
//  int tile = 0;
//  int tilex = 0;
//  int tiley = 0;
//  int lasttile = 0;
//
//  bool keep = true;
//  while(keep){
//
//    window.clear();
//
//    sdlEventDist.run();
//    sysTime.update();
//
//    initT = endT;
//    endT = sysTime.getTotalTime();
//
//    if((endT - maxFrameTime)>initT){
//      initT = endT - maxFrameTime;
//    }
//
////    int pos = (endT/zbe::SECOND)%10;
////    if(pos % 2) {
////      blockInv.setInvisible();
////    } else {
////      blockInv.setVisible();
////    }
////
////    block.setX(pos);
//
//    //board.setTile(tilex, tiley, 0);
//
//    tile = (endT/(zbe::SECOND/4))%240;
//    tilex = tile % 10;
//    tiley = tile / 10;
//
//   // board.setTile(tilex, tiley, 1);
//    if(lasttile != tile) {
//      lasttile = tile;
//      tetromino.drop();
//    }
//    //tetromino.setType((tile / 4) % 8, tile % 4);
//
//    //printf("Tile: %d (%d, %d)\n", tile, tilex, tiley);
//
//    while (initT < endT) {
//      ieg.generate(initT,endT);
//      teg.generate(initT,endT);
//      ceg.generate(initT,endT);
//
//      int64_t eventTime = store.getTime();
//      if (eventTime <= endT) {
//        dMaster.run(eventTime-initT);
//        store.manageCurrent();
//        initT = eventTime;
//      } else {
//        dMaster.run(endT-initT);
//        store.clearStore();
//        initT = endT;
//      }
//    }
//
//    for(auto s : sprites){
//        drawer.apply(s->getSimpleSprite().get());
//    }
//
//    /* If one or more error occurs, the ammount and the first one
//     * wille be stored into SysError estructure, so it can be consulted.
//     *
//     * If there are errors, the first one will be prompted.
//     */
//    int errcount = zbe::SysError::getNErrors();
//    if(errcount>0){
//        printf("Error: %s",zbe::SysError::getFirstErrorString().c_str());fflush(stdout);
//    }
//    window.present();
//  }
//
  return (0);
}

