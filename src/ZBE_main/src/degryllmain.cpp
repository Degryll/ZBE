#include "degryllmain.h"

#include <cstdio>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <chaiscript/chaiscript.hpp>

//#include "ZBE/core/zbe.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
//#include "ZBE/core/events/handlers/InputHandler.h"
//#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/tools/containers/TicketedForwardList.h"

#include "ZBE/core/daemons/MainLoop.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"
#include "ZBE/core/daemons/Punishers.h"

#include "ZBE/core/io/Input.h"

#include "ZBE/core/events/generators/util/InputStatusManager.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
//#include "ZBE/core/events/generators/TimeEventGenerator.h"

#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"
#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
#include "ZBE/SDL/drawers/ConsoleTextSDLDrawer.h"
#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"
#include "ZBE/core/daemons/MainLoopExit.h"
#include "ZBE/events/handlers/input/DaemonIH.h"
#include "ZBE/events/handlers/input/AddText.h"
#include "ZBE/events/handlers/input/ExecuteCommandIH.h"
#include "ZBE/events/handlers/input/RemoveGlyphIH.h"
#include "ZBE/events/handlers/input/ScrollIH.h"

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/behaviors/CustomMotion.h"

#include "ZBE/entities/implementations/Console.h"

class ChaiWarp {
public:
  ChaiWarp(std::shared_ptr<zbe::Value<zbe::Vector2D > > vv) : vv(vv) {}

  void setX(double x) {
    zbe::Vector2D aux(vv->get());
    aux.x = x;
    vv->set(aux);
  }

  void setY(double y) {
    zbe::Vector2D aux(vv->get());
    aux.y = y;
    vv->set(aux);
  }

  void incrementX(double x) {
    zbe::Vector2D aux(vv->get());
    aux.x = aux.x + x;
    vv->set(aux);
  }

  void incrementY(double y) {
    zbe::Vector2D aux(vv->get());
    aux.y = aux.y + y;
    vv->set(aux);
  }

private:
  std::shared_ptr<zbe::Value<zbe::Vector2D > > vv;
};

class ChaiWarpBhv {
public:
  ChaiWarpBhv(std::shared_ptr<zbe::CustomMotion<2> > cm) : cm(cm) {}

  void setFunction(std::function<void(double &posx, double &posy, double &velx, double &vely, double &acelx, double &acely, double time)> f) {
    cm->setFunction(f);
  }

private:
  std::shared_ptr<zbe::CustomMotion<2> > cm;
};

void test2(double &posx, double &, double &velx, double &, double &acelx, double &, double time) {
  acelx = 100.0 * (500.0 - 2.0 * posx + 140.0) / (500.0 - 140.0);
  velx = velx + (acelx * time);
  posx = posx + (velx * time);
}

void test(double &posx, double &, double &velx, double &, double &, double &, double time) {
  posx = posx + (velx * time);
  if (posx > 500) {
    posx = 140 + posx - 500;
  }
}

int degryllmain(int, char*[]) {
  const int WINDOWPOSX = 50;
  const int WINDOWPOSY = 50;
  const int WIDHT = 640;
  const int HEIGHT = 480;
  const int FONTSIZE = 14;
  const int FONTWHITE = 192;
  const int FONTOPACITY = 255;
  const uint64_t INPUTEVENT = 1;
  const uint64_t TEXTEVENT = 2;

  auto chai = std::make_shared<chaiscript::ChaiScript>();

  chai->eval(R"(
    //puts(helloWorld("Bob"));
    print("ChaiScript funcionando!");
  )");

//  std::shared_ptr<zbe::SDLOGLWindow> window = std::make_shared<zbe::SDLOGLWindow>("Console", WINDOWPOSX, WINDOWPOSY, WIDHT, HEIGHT);
  std::shared_ptr<zbe::SDLWindow> window = std::make_shared<zbe::SDLWindow>("Console", WINDOWPOSX, WINDOWPOSY, WIDHT, HEIGHT);
  auto is = window->getImgStore();
  auto gid = is->loadImg("data/images/degryll/isotetris/sueloG.png");
  auto fs = window->getFontStore();
  auto fid = fs->loadFont("data/fonts/Hack-Regular.ttf", FONTSIZE, {FONTWHITE, FONTWHITE, FONTWHITE, FONTOPACITY});

  std::shared_ptr<zbe::DaemonMaster> pre = std::make_shared<zbe::DaemonMaster>();
  std::shared_ptr<zbe::DaemonMaster> post = std::make_shared<zbe::DaemonMaster>();
  std::shared_ptr<zbe::DaemonMaster> event = std::make_shared<zbe::DaemonMaster>();
  std::shared_ptr<zbe::DaemonMaster> common = std::make_shared<zbe::DaemonMaster>();
  std::shared_ptr<zbe::DaemonMaster> react = std::make_shared<zbe::DaemonMaster>();
  std::shared_ptr<zbe::DaemonMaster> draw = std::make_shared<zbe::DaemonMaster>();
  std::shared_ptr<zbe::MainLoop> loop = std::make_shared<zbe::MainLoop>(pre, post, event, common, react, draw);

  std::shared_ptr<zbe::Daemon> preLoopSDL = std::make_shared<zbe::BasicPreLoopSDLDaemon>(window);
  pre->addDaemon(preLoopSDL);
  std::shared_ptr<zbe::Daemon> postLoopSDL = std::make_shared<zbe::BasicPostLoopSDLDaemon>(window);
  post->addDaemon(postLoopSDL);

  auto sysTimer = std::make_shared<zbe::SDLTimer>(true);
  std::shared_ptr<zbe::SysTime> sysTime = zbe::SysTime::getInstance();
  sysTime->setSystemTimer(sysTimer);

  zbe::SDLEventDispatcher& sdlEDispatcher = zbe::SDLEventDispatcher::getInstance();
  std::shared_ptr<zbe::InputBuffer> inputBuffer = sdlEDispatcher.getInputBuffer();
  std::shared_ptr<zbe::InputTextBuffer> inputTextBuffer = sdlEDispatcher.getInputTextBuffer();

  std::shared_ptr<zbe::Value<uint64_t> > fidv = std::make_shared<zbe::SimpleValue<uint64_t> >(fid);
  std::shared_ptr<zbe::Value<std::string> > vc = std::make_shared<zbe::SimpleValue<std::string> >();
  std::shared_ptr<zbe::Value<int64_t> > vl = std::make_shared<zbe::SimpleValue<int64_t> >();
  std::shared_ptr<zbe::Value<std::vector<std::string> > > vh = std::make_shared<zbe::SimpleValue<std::vector<std::string> > >();
  std::shared_ptr<zbe::Console> console = std::make_shared<zbe::Console>(fidv, vc, vl, vh);
  std::shared_ptr<zbe::TextHandler> addText = std::make_shared<zbe::AddText>(vc, vl, vh);

  std::shared_ptr<zbe::Value<uint64_t> > gidv = std::make_shared<zbe::SimpleValue<uint64_t> >(gid);
  std::shared_ptr<zbe::Value<zbe::Vector2D > > sizev = std::make_shared<zbe::SimpleValue<zbe::Vector2D > >(zbe::Vector2D{16.0, 9.0});
  std::shared_ptr<zbe::Value<zbe::Vector2D > > acelv = std::make_shared<zbe::SimpleValue<zbe::Vector2D > >(zbe::Vector2D{0.0, 0.0});
  std::shared_ptr<zbe::Value<zbe::Vector2D > > velv = std::make_shared<zbe::SimpleValue<zbe::Vector2D > >(zbe::Vector2D{100.0, 0.0});
  std::shared_ptr<zbe::Value<zbe::Vector2D > > posv = std::make_shared<zbe::SimpleValue<zbe::Vector2D > >(zbe::Vector2D{320.0, 300.0});
  std::shared_ptr<zbe::Entity> prota = std::make_shared<zbe::Entity>();
  prota->setUint(1, gidv);
  prota->setVector2D(1, sizev);
  prota->setVector2D(2, acelv);
  prota->setVector2D(3, velv);
  prota->setVector2D(4, posv);

  chai->add(chaiscript::fun(&ChaiWarp::setX), "setX");
  chai->add(chaiscript::fun(&ChaiWarp::setY), "setY");
  chai->add(chaiscript::fun(&ChaiWarp::incrementX), "incrementX");
  chai->add(chaiscript::fun(&ChaiWarp::incrementY), "incrementY");
  ChaiWarp chaiacel(acelv);
  chai->add(chaiscript::var(&chaiacel), "acelv");
  ChaiWarp chaivel(velv);
  chai->add(chaiscript::var(&chaivel), "velv");
  ChaiWarp chaipos(posv);
  chai->add(chaiscript::var(&chaipos), "posv");

  std::shared_ptr<zbe::InputEventGenerator> ieg = std::make_shared<zbe::InputEventGenerator>(inputBuffer, inputTextBuffer, TEXTEVENT, addText);
  std::shared_ptr<zbe::MappedInputStatusManager> ism = std::make_shared<zbe::MappedInputStatusManager>(INPUTEVENT);
  ieg->addManager(ism);

  event->addDaemon(ieg);

  auto exitv = std::make_shared<zbe::SimpleValue<int64_t> >();
  std::shared_ptr<zbe::Daemon> exitd = std::make_shared<zbe::MainLoopExit>(loop, exitv, 42);
  zbe::DaemonIH exitih(exitd);
  ism->addHandler(zbe::ZBEK_ESCAPE, &exitih);

  // [TODO] input manager recibe un puntero, deberia ser un shared_ptr
  zbe::ExecuteCommandIH execute(chai, vc, vl, vh);
  ism->addHandler(zbe::ZBEK_RETURN, &execute);
  zbe::RemoveGlyphIH del(vc);
  ism->addHandler(zbe::ZBEK_BACKSPACE, &del);
  zbe::ScrollIH scroll(vl, vh);
  ism->addHandler(zbe::ZBEK_MOUSE_WHEEL_Y, &scroll);

  std::array<uint64_t, 4> l{ {1, 1, 1, 1} };
  std::shared_ptr<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > > cavatar = std::make_shared<zbe::MBaseAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > >(console, l);
  auto cdl = std::make_shared<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > > >();
  cdl->push_front(cavatar);
  std::shared_ptr<zbe::Daemon> drawerDaemon = std::make_shared<zbe::BehaviorDaemon<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > >, uint64_t, std::string, int64_t, std::vector<std::string> > >(std::make_shared<zbe::ConsoleTextDrawer>(window), cdl);
  draw->addDaemon(drawerDaemon);

  std::array<uint64_t, 3> a1{ {1, 1, 4} };
  std::shared_ptr<zbe::MAvatar<uint64_t, zbe::Vector2D, zbe::Vector2D > > protadraw = std::make_shared<zbe::MBaseAvatar<uint64_t, zbe::Vector2D, zbe::Vector2D > >(prota, a1);
  auto pdl = std::make_shared<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, zbe::Vector2D, zbe::Vector2D> > >();
  pdl->push_front(protadraw);
  std::shared_ptr<zbe::Daemon> drawerDaemon2 = std::make_shared<zbe::BehaviorDaemon<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, zbe::Vector2D, zbe::Vector2D> >, uint64_t, zbe::Vector2D, zbe::Vector2D> >(std::make_shared<zbe::SingleSpriteSDLDrawer>(window), pdl);
  draw->addDaemon(drawerDaemon2);

  std::array<uint64_t, 3> a2{ {2, 3, 4} };
  std::shared_ptr<zbe::MAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector2D > > protamove = std::make_shared<zbe::MBaseAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector2D > >(prota, a2);
  auto pml = std::make_shared<zbe::TicketedForwardList<zbe::MAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector2D> > >();
  pml->push_front(protamove);
  auto movebehavior = std::make_shared<zbe::CustomMotion<2> >();
  movebehavior->setFunction(test);
  std::shared_ptr<zbe::Daemon> moveDaemon = std::make_shared<zbe::BehaviorDaemon<zbe::TicketedForwardList<zbe::MAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector2D> >, zbe::Vector2D, zbe::Vector2D, zbe::Vector2D> >(movebehavior, pml);
  common->addDaemon(moveDaemon);

  ChaiWarpBhv chaicm(movebehavior);
  chai->add(chaiscript::fun(&ChaiWarpBhv::setFunction), "setFunction");
  chai->add(chaiscript::var(&chaicm), "movebehavior");
  chai->add(chaiscript::fun(&test), "test");
  chai->add(chaiscript::fun(&test2), "test2");

  loop->run();

  return 0;
}
