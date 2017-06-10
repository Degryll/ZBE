#include "degryllmain.h"

#include <cstdio>
#include <algorithm>

#include "ZBE/archetypes/Drawable.h"
//#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/tools/containers/ResourceManager.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/SDL/system/Window.h"
#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"
#include "ZBE/core/daemons/DaemonMaster.h"
#include "ZBE/core/daemons/Punishers.h"
#include "ZBE/entities/adaptors/SimpleDrawableSingleSpriteAdaptor.h"

#include "game/events/handlers/ExitInputHandler.h"

class GameReactor {};

//namespace zbetris {
//
//class Block: public zbe::Drawable,
//             public zbe::AvatarEntityAdapted<zbe::SingleSprite> {
//public:
//  Block() : x(0), y(0), t(0), lm(zbe::ResourceManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> >::getInstance()), ticket(nullptr) {}
//  Block(int64_t x, int64_t y, uint64_t t, uint64_t id) : x(x), y(y), t(t), lm(zbe::ResourceManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite>*> >::getInstance()), ticket(lm.get(id)->push_front(this)) {}
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
//  zbe::ResourceManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite>*> >& lm;
//  std::shared_ptr<zbe::TicketedElement<zbe::AvatarEntity<zbe::SingleSprite>*> > ticket;
//};
//
//class SimpleDrawableBoardSpriteAdaptor : public zbe::Adaptor<zbe::SingleSprite> {
//public:
//  SimpleDrawableBoardSpriteAdaptor(const SimpleDrawableBoardSpriteAdaptor&) = delete;
//  void operator=(const SimpleDrawableBoardSpriteAdaptor&) = delete;
//
//  SimpleDrawableBoardSpriteAdaptor(int topLeftX, int topLeftY, int tileW, int tileH, zbe::Drawable* entity) : x(topLeftX), y(topLeftY), w(tileW), h(tileH), e(entity), s(nullptr) {}
//
//  virtual ~SimpleDrawableBoardSpriteAdaptor() {
//    delete s;
//  }
//
//  zbe::SingleSprite* getAvatar() {
//    delete s;
//    s = new zbe::SingleSprite();
//
//    s->x = e->getX() * w + x;
//    s->y = e->getY() * w + y;
//    s->w = w;
//    s->h = h;
//    s->graphics = e->getGraphics();
//
//    return (s);
//  }
//
//private:
//  int64_t x;
//  int64_t y;
//  int64_t w;
//  int64_t h;
//  zbe::Drawable* e;
//  zbe::SingleSprite* s;
//};
//
//class Board {
//public:
//  Board(int width, int height, uint64_t t, uint64_t id) : w(width), h(height), b(new int[w*h]), bb(new Block[w*h]()), lines(0) {
//    for(int i = 0; i < height; i++) {
//      for(int j = 0; j < width; j++) {
//        b[i*width+j] = 0;
//        bb[i*width+j].addTo(id);
//        bb[i*width+j].setX(j);
//        bb[i*width+j].setY(i);
//        bb[i*width+j].setType(t);
//        bb[i*width+j].setInvisible();
//
//
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbetris::SimpleDrawableBoardSpriteAdaptor>(100, 100, 32, 32, bb + (i*width+j));
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(bb + (i*width+j)))->setAdaptor(spriteAdaptor);
//      }
//    }
//  }
//
//  void setValue(int x, int y, uint64_t t) {
//    b[y*w+x] = t;
//    if(t) bb[y*w+x].setVisible();
//    else bb[y*w+x].setInvisible();
//  }
//
//  void setTile(int x, int y, uint64_t t) {
//    setValue(x, y, t);
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
//  void check() {
//    for(int i = h-1; i >= 0; i--) {
//        int o = 0;
//      for(int j = 0; j < w; j++) {
//        o += b[i*w+j];
//      }
//      if (o == w) {
//        lines++;
//        if(lines > 9) {apaga(); return;}
//        printf("lines: %d\n", lines);
//        for(int k = i; k > 0; k--) {
//          for(int l = 0; l < w; l++) {
//            setValue(l, k, b[(k-1)*w+l]);
//          }
//        }
//        for(int l = 0; l < w; l++) {
//          b[l] = 0;
//        }
//        i++;
//      }
//    }
//  }
//
//
//  void setLines(int lines) {this->lines = lines;}
//  int getLines() {return (lines);}
//
//  void apaga() {
//    for(int i = 0; i < h; i++) {
//      for(int j = 0; j < w; j++) {
//        bb[i*w+j].setInvisible();
//      }
//    }
//  }
//
//private:
//  int w;
//  int h;
//  int *b;
//  Block* bb;
//  int lines;
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
//  Tetromino(uint64_t img, uint64_t id, Board& board, int type = 0) : b(), x(5), y(3), t(type), r(0), board(board) {
//    for(uint64_t i = 0; i < 4; i++) {
//      b[i].addTo(id);
//      //b[i].setType(type);
//      std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbetris::SimpleDrawableBoardSpriteAdaptor>(100, 100, 32, 32, b + i);
//      ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(b + i))->setAdaptor(spriteAdaptor);
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
//      if (board.getLines() > 9) {
//        for(uint64_t i = 0; i < 4; i++) {
//          b[i].setInvisible();
//        }
//      } else {
//      x = 5;
//      y = 3;
//      //t = (t+1) % 8;
//      t = (rand() % 7) + 1;
//      setPosition();
//      }
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
//    board.check();
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

//}  // namespace zbe
//
//namespace isolux {
//
//class Mitil : public zbe::Drawable,
//              public zbe::AvatarEntityAdapted<zbe::SingleSprite> {
//public:
//  Mitil(int x, int y, int width, int height, int graphics, uint64_t id)
//  : x(x), y(y), w(width), h(height), g(graphics),
//    lm(zbe::ResourceManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite>*> >::getInstance()),
//    ticket(lm.get(id)->push_front(this)) {}
//
////  void setData(int x, int y, int width, int height, int graphics) {
////    this.x = x;
////    this.y = y;
////    this.w = width;
////    this.h = height;
////    this.g = graphics;
////  }
//
//  void setX(int x) {this->x = x;}
//  void setY(int y) {this->y = y;}
//  void setW(int w) {this->w = w;}
//  void setH(int h) {this->h = h;}
//  void setG(int g) {this->g = g;}
//
//  int64_t getX() {return (x);}
//  int64_t getY() {return (y);}
//  int64_t getW() {return (w);}
//  int64_t getH() {return (h);}
//  uint64_t getGraphics() {return (g);}
//
//  void setVisible()   {ticket->setACTIVE();}    //!< The block will be visible.
//  void setInvisible() {ticket->setINACTIVE();}  //!< The block will be invisible.
//  void setERASED()    {ticket->setERASED();}    //!< The block won't be used anymore.
//
//private:
//  int x;
//  int y;
//  int w;
//  int h;
//  int g;
//  zbe::ResourceManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite>*> >& lm;
//  std::shared_ptr<zbe::TicketedElement<zbe::AvatarEntity<zbe::SingleSprite>*> > ticket;
//};
//
//class MiMap {
//public:
//  MiMap(const MiMap&) = delete;
//  void operator=(const MiMap&) = delete;
//
//  MiMap(int x, int y, int width, int height, int levels, int *mapa, int tileWidth, int tileHeight, int g, uint64_t id)
//  : x(x), y(y), width(width), height(height), levels(levels), tileWidth(tileWidth), tileHeight(tileHeight),
//    g(g), id(id), hw(tileWidth/2), hh(tileHeight/2), lvl(height*width), cx(30), cy(22), isActive(false),
//    mapa(mapa), m(width * height, nullptr), s0(width * height, nullptr),
//    i1(width * height, nullptr), d1(width * height, nullptr), s1(width * height, nullptr),
//    i2(width * height, nullptr), d2(width * height, nullptr), s2(width * height, nullptr),
//    i3(width * height, nullptr), d3(width * height, nullptr), s3(width * height, nullptr),
//    i4(width * height, nullptr), d4(width * height, nullptr), s4(width * height, nullptr),
//    arcade(nullptr), character(nullptr), musica(nullptr), muros(nullptr) {
//
//    create();
//  }
//
//  void create() {
//    arcade = new Mitil(x + 31 * tileWidth - 7, y + 21 * hh - 38, 26, 47, g+7, id);
//    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptorArcade = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(arcade);
//    ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(arcade))->setAdaptor(spriteAdaptorArcade);
//
//    arcade->setInvisible();
//
//    character = new Mitil(x + cx * tileWidth + 4, y + cy * hh - 31, 11, 38, g+3, id);
//    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptorChar = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(character);
//    ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(character))->setAdaptor(spriteAdaptorChar);
//
//    character->setInvisible();
//
//    musica = new Mitil(x, y + 300, 673, 271, g+8, id);
//    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptormusica = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(musica);
//    ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(musica))->setAdaptor(spriteAdaptormusica);
//
//    musica->setInvisible();
//
//    muros = new Mitil(x, y + 300, 673, 271, g+9, id);
//    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptormuros = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(muros);
//    ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(muros))->setAdaptor(spriteAdaptormuros);
//
//    muros->setInvisible();
//
//
//    for(int i = 0; i < height; i++) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = 0; j < width; j++) {
//        s4[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 9 - 9 - 9 - 9, tileWidth, tileHeight, g, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor14 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s4[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s4[i*width+j]))->setAdaptor(spriteAdaptor14);
//        s4[i * width + j]->setInvisible();
//      }
//    }
//
//    for(int i = height-1; i >= 0; i--) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = width-1; j >= 0; j--) {
//        d4[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 5 - 9 - 9 - 9, 8, 14, g+1, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor13 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(d4[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(d4[i*width+j]))->setAdaptor(spriteAdaptor13);
//
//        i4[i * width + j] = new Mitil(x + j * tileWidth + offset+8, y + i * hh - 5 - 9 - 9 - 9, 8, 14, g+2, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor12 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(i4[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(i4[i*width+j]))->setAdaptor(spriteAdaptor12);
//        d4[i * width + j]->setInvisible();
//        i4[i * width + j]->setInvisible();
//      }
//    }
//
//    for(int i = 0; i < height; i++) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = 0; j < width; j++) {
//        s3[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 9 - 9 - 9, tileWidth, tileHeight, g, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor11 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s3[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s3[i*width+j]))->setAdaptor(spriteAdaptor11);
//        s3[i * width + j]->setInvisible();
//      }
//    }
//
//    for(int i = height-1; i >= 0; i--) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = width-1; j >= 0; j--) {
//        d3[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 5 - 9 - 9, 8, 14, g+1, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor10 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(d3[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(d3[i*width+j]))->setAdaptor(spriteAdaptor10);
//
//        i3[i * width + j] = new Mitil(x + j * tileWidth + offset+8, y + i * hh - 5 - 9 - 9, 8, 14, g+2, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor9 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(i3[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(i3[i*width+j]))->setAdaptor(spriteAdaptor9);
//        d3[i * width + j]->setInvisible();
//        i3[i * width + j]->setInvisible();
//      }
//    }
//
//    for(int i = 0; i < height; i++) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = 0; j < width; j++) {
//        s2[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 9 - 9, tileWidth, tileHeight, g, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor8 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s2[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s2[i*width+j]))->setAdaptor(spriteAdaptor8);
//        s2[i * width + j]->setInvisible();
//      }
//    }
//
//    for(int i = height-1; i >= 0; i--) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = width-1; j >= 0; j--) {
//        d2[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 5 - 9, 8, 14, g+1, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor7 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(d2[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(d2[i*width+j]))->setAdaptor(spriteAdaptor7);
//
//        i2[i * width + j] = new Mitil(x + j * tileWidth + offset+8, y + i * hh - 5 - 9, 8, 14, g+2, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor6 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(i2[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(i2[i*width+j]))->setAdaptor(spriteAdaptor6);
//        d2[i * width + j]->setInvisible();
//        i2[i * width + j]->setInvisible();
//      }
//    }
//
//    for(int i = 0; i < height; i++) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = 0; j < width; j++) {
//        s1[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 9, tileWidth, tileHeight, g, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor5 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s1[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s1[i*width+j]))->setAdaptor(spriteAdaptor5);
//        s1[i * width + j]->setInvisible();
//      }
//    }
//
//    for(int i = height-1; i >= 0; i--) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = width-1; j >= 0; j--) {
//        d1[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 5, 8, 14, g+1, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor4 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(d1[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(d1[i*width+j]))->setAdaptor(spriteAdaptor4);
//
//        i1[i * width + j] = new Mitil(x + j * tileWidth + offset+8, y + i * hh - 5, 8, 14, g+2, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor3 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(i1[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(i1[i*width+j]))->setAdaptor(spriteAdaptor3);
//        d1[i * width + j]->setInvisible();
//        i1[i * width + j]->setInvisible();
//      }
//    }
//
//    for(int i = 0; i < height; i++) {
//      int offset = (i % 2) ? hw : 0;
//      for(int j = 0; j < width; j++) {
//        s0[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh, tileWidth, tileHeight, g, id);
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor2 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s0[i*width+j]);
//        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s0[i*width+j]))->setAdaptor(spriteAdaptor2);
//        s0[i * width + j]->setInvisible();
//      }
//    }
//  }
//
//  void activate() {
//    isActive = true;
//    arcade->setVisible();
//    character->setVisible();
//    musica->setVisible();
//
//    for(int i = 0; i < height; i++) {
//      for(int j = 0; j < width; j++) {
//        if (mapa[lvl*3 + i*width+j] != 0) {
//            s4[i * width + j]->setVisible();
//        }
//      }
//    }
//
//    for(int i = height-1; i >= 0; i--) {
//      for(int j = width-1; j >= 0; j--) {
//        if (mapa[lvl*3 + i*width+j] != 0) {
//            d4[i * width + j]->setVisible();
//            i4[i * width + j]->setVisible();
//        }
//      }
//    }
//
//    for(int i = 0; i < height; i++) {
//      for(int j = 0; j < width; j++) {
//        if (mapa[lvl*2 + i*width+j] == 0) {
//            s3[i * width + j]->setInvisible();
//        }
//      }
//    }
//
//    for(int i = height-1; i >= 0; i--) {
//      for(int j = width-1; j >= 0; j--) {
//        if (mapa[lvl*2 + i*width+j] != 0) {
//            d3[i * width + j]->setVisible();
//            i3[i * width + j]->setVisible();
//        }
//      }
//    }
//
//    for(int i = 0; i < height; i++) {
//      for(int j = 0; j < width; j++) {
//        if (mapa[lvl + i*width+j] != 0) {
//            s2[i * width + j]->setVisible();
//        }
//      }
//    }
//
//    for(int i = height-1; i >= 0; i--) {
//      for(int j = width-1; j >= 0; j--) {
//        if (mapa[lvl + i*width+j] != 0) {
//            d2[i * width + j]->setVisible();
//            i2[i * width + j]->setVisible();
//        }
//      }
//    }
//
//    for(int i = 0; i < height; i++) {
//      for(int j = 0; j < width; j++) {
//        if (mapa[i*width+j] != 0) {
//            s1[i * width + j]->setVisible();
//        }
//      }
//    }
//
//    for(int i = height-1; i >= 0; i--) {
//      for(int j = width-1; j >= 0; j--) {
//        if (mapa[i*width+j] != 0) {
//            d1[i * width + j]->setVisible();
//            i1[i * width + j]->setVisible();
//        }
//      }
//    }
//
//    for(int i = 0; i < height; i++) {
//      for(int j = 0; j < width; j++) {
//          s0[i * width + j]->setVisible();
//      }
//    }
//  }
//
//  void setCharPos(int g) {
//    int offset = (cy % 2) ? hw : 0;
//    character->setX(x + cx * tileWidth + offset + 4);
//    character->setY(y + cy * hh - 31);
//    character->setG(g);
//
//    if ((cx == 30) && cy == 22) {
//      musica->setVisible();
//    } else {
//      musica->setInvisible();
//    }
//
//    if (cy > 38) {
//      muros->setVisible();
//    } else if ((cx < 7) && (cy < 30)) {
//      muros->setVisible();
//    } else {
//      muros->setInvisible();
//    }
//  }
//
//  void movecu() {
//    if (!isActive) return;
//    if(cy % 2) {
//      if (mapa[(cy-1)*width+(cx+1)] == 0) {cy--; cx++;}
//    } else {
//      if (mapa[(cy-1)*width+cx] == 0) {cy--;}
//    }
//    setCharPos(g+3);
//  }
//
//  void movecd() {
//    if (!isActive) return;
//    if(cy % 2) {
//      if (mapa[(cy+1)*width+cx] == 0) {cy++;}
//    } else {
//      if (mapa[(cy+1)*width+(cx-1)] == 0) {cy++; cx--;}
//    }
//    setCharPos(g+4);
//  }
//
//  void movecl() {
//    if (!isActive) return;
//    if(cy % 2) {
//      if (mapa[(cy-1)*width+cx] == 0) {cy--;}
//    } else {
//      if (mapa[(cy-1)*width+(cx-1)] == 0) {cy--; cx--;}
//    }
//    setCharPos(g+5);
//  }
//
//  void movecr() {
//    if (!isActive) return;
//    if(cy % 2) {
//      if (mapa[(cy+1)*width+(cx+1)] == 0) {cy++; cx++;}
//    } else {
//      if (mapa[(cy+1)*width+cx] == 0) {cy++;}
//    }
//    setCharPos(g+6);
//  }
//
//private:
//  int x;
//  int y;
//  int width;
//  int height;
//  int levels;
//  int tileWidth;
//  int tileHeight;
//  int g;
//  uint64_t id;
//  int hw;
//  int hh;
//  int lvl;
//  int cx;
//  int cy;
//  bool isActive;
//  int *mapa;
//  std::vector<Mitil*> m;
//  std::vector<Mitil*> s0;
//  std::vector<Mitil*> i1;
//  std::vector<Mitil*> d1;
//  std::vector<Mitil*> s1;
//  std::vector<Mitil*> i2;
//  std::vector<Mitil*> d2;
//  std::vector<Mitil*> s2;
//  std::vector<Mitil*> i3;
//  std::vector<Mitil*> d3;
//  std::vector<Mitil*> s3;
//  std::vector<Mitil*> i4;
//  std::vector<Mitil*> d4;
//  std::vector<Mitil*> s4;
//  Mitil* arcade;
//  Mitil* character;
//  Mitil* musica;
//  Mitil* muros;
//};
//
//class MoveCUInputHandler : public zbe::InputHandler {
//	public:
//	  MoveCUInputHandler(const MoveCUInputHandler&) = delete;
//	  void operator=(const MoveCUInputHandler&) = delete;
//
//  	MoveCUInputHandler(MiMap& mapa) : m(mapa) {}
//
//  	void run(float status) {
//      if( status) {
//          m.movecu();
//      }
//  	}
//
//	private:
//    MiMap& m;
//};
//
//class MoveCDInputHandler : public zbe::InputHandler {
//	public:
//	  MoveCDInputHandler(const MoveCDInputHandler&) = delete;
//	  void operator=(const MoveCDInputHandler&) = delete;
//
//  	MoveCDInputHandler(MiMap& mapa) : m(mapa) {}
//
//  	void run(float status) {
//      if( status) {
//          m.movecd();
//      }
//  	}
//
//	private:
//    MiMap& m;
//};
//
//class MoveCLInputHandler : public zbe::InputHandler {
//	public:
//	  MoveCLInputHandler(const MoveCLInputHandler&) = delete;
//	  void operator=(const MoveCLInputHandler&) = delete;
//
//  	MoveCLInputHandler(MiMap& mapa) : m(mapa) {}
//
//  	void run(float status) {
//      if( status) {
//          m.movecl();
//      }
//  	}
//
//	private:
//    MiMap& m;
//};
//
//class MoveCRInputHandler : public zbe::InputHandler {
//	public:
//	  MoveCRInputHandler(const MoveCRInputHandler&) = delete;
//	  void operator=(const MoveCRInputHandler&) = delete;
//
//  	MoveCRInputHandler(MiMap& mapa) : m(mapa) {}
//
//  	void run(float status) {
//      if( status) {
//          m.movecr();
//      }
//  	}
//
//	private:
//    MiMap& m;
//};
//
//}  // namespace isolux
//
void loadMap(const char* filename, int** m, int& w, int& h, int& l) {
  FILE *f = fopen(filename, "r");
  fscanf(f, "%d %d %d", &w, &h, &l);
  printf("mapa: %d %d %d\n", w, h, l);
  *m = (int*)malloc(sizeof(int) * w * h * l);
  int *p = *m;
  int idx = 0;
  int aux;
  for(int k = 0; k < l; k++) {
    for(int i = 0; i < h; i++) {
      for(int j = 0; j < w; j++) {
        fscanf(f, "%d ", &aux);
        idx++;
        p[0] = aux;
        p++;
      }
    }
  }

  fclose(f);
}

//void printMap(int* m, int w, int h, int l) {
//  int *p = m;
//  for(int k = 0; k < l; k++) {
//    for(int i = 0; i < h; i++) {
//      for(int j = 0; j < w; j++) {
//          printf("%d", p[0]);
//          p++;
//      }
//      printf("\n");
//    }
//    printf("--------------------------------------------------\n");
//  }
//}

class MultiLevelMap {
public:
  MultiLevelMap(const MultiLevelMap&) = delete;
  void operator=(const MultiLevelMap&) = delete;

  MultiLevelMap(int width, int height, int depth) : m(new int[width*height*depth]), w(width), h(height), d(depth), hw(w/2), hh(h/2), hd(d/2) {}
  MultiLevelMap(int width, int height, int depth, int* map) : m(new int[width*height*depth]), w(width), h(height), d(depth), hw(w/2), hh(h/2), hd(d/2) {
    std::copy(map, map + (w*h*d), m);
  }

  void setTile(int width, int height, int depth, int value) {m[(height * w + width) * d + depth] = value;}

  int getTile(int width, int height, int depth) {return (m[(height * w + width) * d + depth]);}
  int getTile(int position) {return (m[position]);}

  int getW() {return (w);}
  int getH() {return (h);}
  int getD() {return (d);}
  int getHW() {return (hw);}
  int getHH() {return (hh);}
  int getHD() {return (hd);}

private:
  int *m;
  int w, h, d;
  int hw, hh, hd;
};

struct TileComparator {
  bool operator() (const zbe::Point<3>& lhs, const zbe::Point<3>& rhs) const {
    if (lhs[3] < rhs[3]) {return true;}
    else if (lhs[3] > rhs[3]) {return false;}

    if (lhs[2] < rhs[2]) {return true;}
    else if (lhs[2] > rhs[2]) {return false;}

    if (lhs[1] < rhs[1]) {return true;}
    else if (lhs[1] > rhs[1]) {return false;}

    return false;
  }
};


class IsometricDrawer {
public:
  IsometricDrawer(const IsometricDrawer&) = delete;
  void operator=(const IsometricDrawer&) = delete;

  IsometricDrawer(MultiLevelMap* map, uint64_t groundImage, uint64_t lWallImage, uint64_t rWallImage, zbe::Window* window)
  : m(map), grimage(groundImage), lwimage(lWallImage), rwimage(rWallImage), ground(), leftWall(), rightWall(), window(window) {}

  void setMap(MultiLevelMap* map) {m = map;}

  void draw();

private:
  MultiLevelMap* m;
  uint64_t grimage;
  uint64_t lwimage;
  uint64_t rwimage;
  std::set<zbe::Point<3>, TileComparator> ground;
  std::set<zbe::Point<3>, TileComparator> leftWall;
  std::set<zbe::Point<3>, TileComparator> rightWall;
  zbe::Window* window;
};

//void draw() {
//  int x = m->getHW();
//  int y = m->getHH();
//  int z = m->getHD();
//
//  int k = z;
//
//  while((k > 0) && m->getTile(x, y, k) == 0) k--;
//  while((k < (m->getD()-1)) && m->getTile(x, y, k) == 1) k++;
//  int ground = k;
//
//  floors.insert({(double)x, (double)y, (double)k});
//
//  while((k < (m->getD()-1)) && m->getTile(x, y, k) == 0) k++;
//  int ceiling = k;
//
//  walkUp();
//  walkUpRight();
//  walkRight();
//  walkDownRight();
//  walkDonw();
//  walkDownLeft();
//  walkLeft();
//  walkUpLeft();
//}
//
//findWalls(int x, int y, int z) {
//  if((y % 2) == 0) {
//    // leftWall only if (X , Y) is at the right:
//    //   - Take Y and go up to a even number, ie. (3 -> 2) or (-3 -> 4)
//    //   - subtract X - (Y/2) if thats is greater or equals to 1, draw the wall.
//    if (m->getTile(x-1, y+1, k) == 0) {leftWall.insert({(double)x, (double)y, (double)z});}
//    if (m->getTile(x,   y+1, k) == 0) {rightWall.insert({(double)x, (double)y, (double)z});}
//  } else {
//    if (m->getTile(x,   y+1, k) == 0) {leftWall.insert({(double)x, (double)y, (double)z});}
//    if (m->getTile(x+1, y+1, k) == 0) {rightWall.insert({(double)x, (double)y, (double)z});}
//  }
//}
//
//int findFloors(int x, int y, int z, int ceiling) {
//  int k = z;
//  while((k > 0) && m->getTile(x, y, k) == 0) k--;
//  while((k < ceiling) && m->getTile(x, y, k) == 1) findWalls(x, y, k++);
//  int ground = k;
//  if(ground < ceiling) {
//    floors.insert({(double)x, (double)y, (double)k});
//  }
//
//  while (k < ceiling) {
//    while((k < ceiling) && m->getTile(j, i, k) == 0) k++;
//    while((k < ceiling) && m->getTile(x, y, k) == 1) findWalls(x, y, k++);
//    if (k < ceiling) {floors.insert({(double)x, (double)y, (double)k});}
//  }
//  return ground;
//}
//
//void walkUp(int x, int y, int z, int ceiling) {
//  y++;
//  // if inside map
//  int ground = findFloors(x, y, z, ceiling);
//
//  walkUp(x, y, ground, ceiling);
//  walkUpRight(x, y, ground, ceiling);
//  walkUpLeft(x, y, ground, ceiling);
//}

/*

- Partir de la posicion del personaje (centro de la cámara)
- buscar suelo (si el personaje está sobre el suelo, ese, si está al aire, descender por niveles hasta encontrarlo).
- Recorrer el mapa primero hacia atras (izq y arriba) y luego hacia adelante (der y abajo).
- Por cada nueva casilla se busca el suelo a partir del suelo contiguo.
  - Si al nivel actual la nueva casilla es aire, se desciende hasta encontrar el suelo.
  - Si hay un bloque solido, se asciende hasta encontrar el nuevo nivel de suelo.

*/

void IsometricDrawer::draw() {
  // - Partir de la posicion del personaje (centro de la cámara)
  // POR AHORA el centro del mapa
  int x = m->getHW();
  int y = m->getHH();
  int z = m->getHD();

  // buscar suelo (si el personaje está sobre el suelo, ese, si está al aire, descender por niveles hasta encontrarlo).
  // POR AHORA siempre esta en el suelo

  // - Recorrer el mapa primero hacia atras (izq y arriba) y luego hacia adelante (der y abajo).
  // POR AHORA 0 es aire y 1 es tierra
  int idx = x;
  int idy = y;
  int idz = z;
  int k = idz;
  // backward from center
  for(int i = idy; i >= 0; i--) {
    for(int j = idx; j >= 0; j--) {
      //printf("x: %d, y: %d, d: %d\n", j, i, k); fflush(stdout);
      // - Por cada nueva casilla se busca el suelo a partir del suelo contiguo.
      //   - Si al nivel actual la nueva casilla es aire, se desciende hasta encontrar el suelo.
      //   - Si hay un bloque solido, se asciende hasta encontrar el nuevo nivel de suelo.
      while((k > 0) && m->getTile(j, i, k) == 0) k--;
      while((k < (m->getD()-1)) && m->getTile(j, i, k) == 1) k++;
      ground.insert({(double)j, (double)i, (double)k});
      //  TODO insertar muros
    }
    idx = m->getW() - 1;
  }

  idx = x + 1;
  k = idz;
  // forward from center
  for(int i = idy; i < m->getH(); i++) {
    for(int j = idx; j < m->getW(); j++) {
      //printf("x: %d, y: %d, d: %d\n", j, i, k); fflush(stdout);
      // - Por cada nueva casilla se busca el suelo a partir del suelo contiguo.
      //   - Si al nivel actual la nueva casilla es aire, se desciende hasta encontrar el suelo.
      //   - Si hay un bloque solido, se asciende hasta encontrar el nuevo nivel de suelo.
      while((k > 0) && m->getTile(j, i, k) == 0) k--;
      while((k < (m->getD()-1)) && m->getTile(j, i, k) == 1) k++;
      ground.insert({(double)j, (double)i, (double)k});
      //  TODO insertar muros
    }
    idx = 0;
  }

  SDL_Rect src,dst;
  for (auto &point : ground) {
    //printf("x: %.1lf, y: %.1lf, d: %.1lf\n", point[0], point[1], point[2]); fflush(stdout);
    const int iw = 16;
    const int ih = 9;
    const int ihw = iw / 2;
    const int ihh = ih / 2;
    src.x = 0;
    src.y = 0;
    src.w = 16;
    src.h = 9;

    int offset = ((int)(point[1]) % 2) ? ihw : 0;

    dst.x = 100 + point[0] * iw + offset;
    dst.y = 100 + point[1] * ihh - ih * point[2];
    dst.w = 16;
    dst.h = 9;
    //printf("x: %d, y: %d\n", dst.x, dst.y); fflush(stdout);
    window->render(grimage, &src, &dst);
  }

}

int degryllmain(int, char**) {
  printf("--- Degryll main ---\n\n");

  const int WIDTH = 1024;
  const int HEIGHT = 768;

  const char floorfilename[] = "data/images/degryll/isotetris/sueloT.png";
  const char izqfilename[] = "data/images/degryll/isotetris/izqT.png";
  const char derfilename[] = "data/images/degryll/isotetris/derT.png";

  zbe::Window window(WIDTH,HEIGHT);
  uint64_t floortile     = window.loadImg(floorfilename);
  uint64_t izqtile       = window.loadImg(izqfilename);
  uint64_t dertile       = window.loadImg(derfilename);
//  window.loadImg(izqfilename);
//  window.loadImg(derfilename);

  const int mapW = 51;
  const int mapH = 51;
  const int mapD = 5;
  int *map = new int[mapW * mapH * mapD];
  for(int i = 0; i < mapH; i++) {
    for(int j = 0; j < mapW; j++) {
      for(int k = 0; k < mapD; k++) {
//          if( k < 2) map[(i * mapW + j) * mapD + k] = 1;//(i < 50);
//          else map[(i * mapW + j) * mapD + k] = 0;
          map[(i * mapW + j) * mapD + k] = 1;
      }
    }
  }
  int value = 0;
  for(int i = 0; i < mapH; i++) {
    for(int j = 0; j < mapW; j++) {
      if((i > 45) || (j > 45)) {
        value = 0;
      } else {
        value = 1;
      }
      map[(i * mapW + j) * mapD + 4] = value;
    }
  }

  for(int i = 0; i < mapH; i++) {
    for(int j = 0; j < mapW; j++) {
      if((i > 46) || (j > 46)) {
        value = 0;
      } else {
        value = 1;
      }
      map[(i * mapW + j) * mapD + 3] = value;
    }
  }

  for(int i = 0; i < mapH; i++) {
    for(int j = 0; j < mapW; j++) {
      if((i > 47) || (j > 47)) {
        value = 0;
      } else {
        value = 1;
      }
      map[(i * mapW + j) * mapD + 2] = value;
    }
  }

  for(int i = 0; i < mapH; i++) {
    for(int j = 0; j < mapW; j++) {
      if((i > 48) || (j > 48)) {
        value = 0;
      } else {
        value = 1;
      }
      map[(i * mapW + j) * mapD + 1] = value;
    }
  }

  for(int i = 0; i < mapH; i++) {
    for(int j = 0; j < mapW; j++) {
      if((i > 49) || (j > 49)) {
        value = 0;
      } else {
        value = 1;
      }
      map[(i * mapW + j) * mapD + 0] = value;
    }
  }
//  map[(50 * mapW + 50) * mapD + 0] = 1;
//  map[(50 * mapW + 50) * mapD + 1] = 0;
//  map[(50 * mapW + 50) * mapD + 2] = 0;
//  map[(50 * mapW + 50) * mapD + 3] = 0;
//  map[(50 * mapW + 50) * mapD + 4] = 0;

  MultiLevelMap isomap(mapW, mapH, mapD, map);
  IsometricDrawer isodrawer(&isomap, floortile, izqtile, dertile, &window);

  bool keep = true;
  while(keep){

    window.clear();
    isodrawer.draw();
    window.present();

    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
  }

  return (0);
}

//int degryllmain(int, char**) {
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
//  int *m;
//  int w, h, l;
//  loadMap("data/images/degryll/isotetris/mapa.txt", &m,  w, h, l);
//  //printMap(m, w, h, l);
//
//  const char blockfilename[] = "data/images/batis/bloque_32.png";
//  const char floorfilename[] = "data/images/degryll/isotetris/sueloT.png";
//  const char izqfilename[] = "data/images/degryll/isotetris/izqT.png";
//  const char derfilename[] = "data/images/degryll/isotetris/derT.png";
//  const char charufilename[] = "data/images/degryll/isotetris/charUT.png";
//  const char chardfilename[] = "data/images/degryll/isotetris/charDT.png";
//  const char charlfilename[] = "data/images/degryll/isotetris/charLT.png";
//  const char charrfilename[] = "data/images/degryll/isotetris/charRT.png";
//  const char arcfilename[] = "data/images/degryll/isotetris/arcadeT.png";
//  const char musicafilename[] = "data/images/degryll/isotetris/musica.png";
//  const char murosfilename[] = "data/images/degryll/isotetris/muros.png";
//  uint64_t blockgraphics;
//  uint64_t floortile;
////  uint64_t izqtile;
////  uint64_t dertile;
////  uint64_t charutile;
////  uint64_t chardtile;
////  uint64_t charltile;
////  uint64_t charrtile;
////  uint64_t arctile;
////  uint64_t musicatile;
////  uint64_t murostile;
//
//  zbe::EventStore& store = zbe::EventStore::getInstance();
//
//  zbe::SDLEventDispatcher & sdlEventDist = zbe::SDLEventDispatcher::getInstance();
//  zbe::InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
//  zbe::InputEventGenerator ieg(inputBuffer,INPUTEVENT);
//
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<GameReactor> >*> ctl;
//  zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<GameReactor> >*> >& lmct = zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<GameReactor> >*> >::getInstance();
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
//  floortile     = window.loadImg(floorfilename);
////  izqtile       = window.loadImg(izqfilename);
////  dertile       = window.loadImg(derfilename);
////  charutile     = window.loadImg(charufilename);
////  chardtile     = window.loadImg(chardfilename);
////  charltile     = window.loadImg(charlfilename);
////  charrtile     = window.loadImg(charrfilename);
////  arctile       = window.loadImg(arcfilename);
////  musicatile    = window.loadImg(musicafilename);
////  murostile     = window.loadImg(murosfilename);
//  window.loadImg(izqfilename);
//  window.loadImg(derfilename);
//  window.loadImg(charufilename);
//  window.loadImg(chardfilename);
//  window.loadImg(charlfilename);
//  window.loadImg(charrfilename);
//  window.loadImg(arcfilename);
//  window.loadImg(musicafilename);
//  window.loadImg(murosfilename);
//
////  zbe::SimpleSpriteSDLDrawer drawer(&window);
//  zbe::DaemonMaster drawMaster;
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> sprites;
//  zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> >& lmdraw = zbe::ResourceManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> >::getInstance();
//  lmdraw.insert(DRAWLIST, &sprites);
//
//  std::shared_ptr<zbe::Daemon> drawerDaemon(new  zbe::DrawerDaemon<zbe::SingleSprite, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> >(std::make_shared<zbe::SingleSpriteSDLDrawer>(&window), DRAWLIST));
//  drawMaster.addDaemon(drawerDaemon);
//
//  zbe::TimedDaemonMaster behavMaster;
////  std::vector<zbe::Mobile<2>*> vmobile;
////  zbe::ResourceManager< std::vector<zbe::Mobile<2>*> >& lmmobile = zbe::ResourceManager< std::vector<zbe::Mobile<2>*> >::getInstance();
////  lmmobile.insert(MOBILELIST, &vmobile);
////  std::shared_ptr<zbe::Daemon> bball(new  zbe::BehaviorDaemon< zbe::Mobile<2>, std::vector<zbe::Mobile<2>*> >(new zbe::UniformLinearMotion<2>(), MOBILELIST));
////  dMaster.addDaemon(bball);
//
////  zbe::Block block(0, 0, blockgraphics, DRAWLIST);
////  block.setSimpleSpriteAdaptor(&blockAdaptor);
////
////  zbe::Block blockInv(0, 1, blockgraphics, DRAWLIST);
////  blockInv.setSimpleSpriteAdaptor(&blockAdaptor);
//
//  zbetris::Board board(10, 20, blockgraphics, DRAWLIST);
//
//  zbetris::Tetromino tetromino(blockgraphics, DRAWLIST, board, 1);
////  //ball
////  std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >*> ballActuatorsList;
////  zbe::ResourceManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >* > >& lmBallActuatorsList = zbe::ResourceManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >* > >::getInstance();
////  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
////  game::GameBallBouncer gbBouncer;
////  ballActuatorsList.push_front(&gbBouncer);
////
////  zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> collisionablesList;
////  zbe::ResourceManager<zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >& lmCollisionablesList = zbe::ResourceManager< zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >::getInstance();
////  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);
//
//
////  zbe::SimpleSpriteAdaptor<zbe::Drawable>* spriteAdaptor = new zbe::SimpleDrawableSimpleSpriteAdaptor();
////  zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2> * movableCatorAdaptor = new zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2>();
//
//  game::ExitInputHandler terminator;
//  ieg.addHandler(zbe::ZBEK_ESCAPE, &terminator);
//
//  zbetris::MoveLeftInputHandler moveleft(tetromino);
//  ieg.addHandler(zbe::ZBEK_a, &moveleft);
//
//  zbetris::MoveRightInputHandler moveright(tetromino);
//  ieg.addHandler(zbe::ZBEK_d, &moveright);
//
//  zbetris::RotateLeftInputHandler rleft(tetromino);
//  ieg.addHandler(zbe::ZBEK_SPACE, &rleft);
//
//  isolux::MiMap isomap(100, 100, w, h, l, m, 16, 9, floortile, DRAWLIST);
//
//  isolux::MoveCUInputHandler mud(isomap);
//  ieg.addHandler(zbe::ZBEK_UP, &mud);
//
//  isolux::MoveCDInputHandler mcd(isomap);
//  ieg.addHandler(zbe::ZBEK_DOWN, &mcd);
//
//  isolux::MoveCLInputHandler mld(isomap);
//  ieg.addHandler(zbe::ZBEK_LEFT, &mld);
//
//  isolux::MoveCRInputHandler mrd(isomap);
//  ieg.addHandler(zbe::ZBEK_RIGHT, &mrd);
//
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
////  zbe::ResourceManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >& lmSimpleConerActuatorsList = zbe::ResourceManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >::getInstance();
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
////  int tilex = 0;
////  int tiley = 0;
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
////    tilex = tile % 10;
////    tiley = tile / 10;
//
//   // board.setTile(tilex, tiley, 1);
//    if ((lasttile != tile) && board.getLines() <= 9) {
//      lasttile = tile;
//      tetromino.drop();
//    }
//    if ((board.getLines() > 9) && (board.getLines() < 30)){
//      isomap.activate();
//      board.setLines(99);
//    }
//    //tetromino.setType((tile / 4) % 8, tile % 4);
//
//    //printf("Tile: %d (%d, %d)\n", tile, tilex, tiley);
//    while (initT < endT) {
//
//      ieg.generate(initT,endT);
//      teg.generate(initT,endT);
//      ceg.generate(initT,endT);
//
//      int64_t eventTime = store.getTime();
//      if (eventTime <= endT) {  zbe::TimedDaemonMaster behavMaster;
//        behavMaster.run(eventTime-initT);
//        store.manageCurrent();
//        initT = eventTime;
//      } else {
//        behavMaster.run(endT-initT);
//        store.clearStore();
//        initT = endT;
//      }
//    }
//
//    drawMaster.run();
////    for(auto s : sprites){
////        drawer.apply(s->getSimpleSprite().get());
////    }
//
//    /* If one or more error occurs, the ammount and the first one
//     * will be stored into SysError structure, so it can be consulted.
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
//  return (0);
//}
