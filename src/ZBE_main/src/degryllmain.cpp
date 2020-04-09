#include "degryllmain.h"

#include <cstdio>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//#include "ZBE/core/zbe.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"
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
#include "ZBE/core/daemons/MainLoopExit.h"
#include "ZBE/events/handlers/input/DaemonIH.h"
#include "ZBE/events/handlers/input/AddText.h"

#include "ZBE/entities/implementations/Console.h"

//class Console : public zbe::Entity {
//public:
//  Console() : vh(std::make_shared<zbe::SimpleValue<std::vector<std::string> > >()),
//              vc(std::make_shared<zbe::SimpleValue<std::string> >("")),
//              vl(std::make_shared<zbe::SimpleValue<int64_t> >(0)) {}
//
//  void addutf8(std::string utf8) {
//    if (SDL_strlen(utf8.c_str()) == 0 || utf8.c_str()[0] == '\n') return;
////    text += utf8;
//    vc->set(vc->get() + utf8);
////    current = historial.size();
//    vl->set(vh->get().size());
//  }
//
//  void removeglyph() {
//    while(1) {
//      if (vc->get().size()==0) {
//        break;
//      }
//      if ((vc->get().back() & 0x80) == 0x00) {
//        /* One byte */
//        vc->get().pop_back();
//        break;
//      }
//      if ((vc->get().back() & 0xC0) == 0x80) {
//        /* Byte from the multibyte sequence */
//        vc->get().pop_back();
//      }
//      if ((vc->get().back() & 0xC0) == 0xC0) {
//        /* First byte of multibyte sequence */
//        vc->get().pop_back();
//        break;
//      }
//    }  // while(1)
//  }
//
//  void execute() {
//    vh->get().push_back(vc->get());
//    vc->get().clear();
////    current++;
//    vl->set(vl->get() + 1);
//  }
//  int first() { return std::max(0ll, vl->get() - 10); }
//  int last() { return (vl->get()); }
//  std::string getLine(size_t lineno) {
//    using namespace std::string_literals;
//    return (">> "s + vh->get()[lineno]);
//  }
//  std::string command() {
//    using namespace std::string_literals;
//    return (">> "s + vc->get());
//  }
//
//  void lookup() {vl->set(std::max(0ll, vl->get()-1));}
//  void lookdown() {vl->set(std::min(int64_t(vh->get().size()), vl->get()+1));}
//
//private:
//  std::shared_ptr<zbe::Value<std::vector<std::string> > > vh;
//  std::shared_ptr<zbe::Value<std::string> > vc;
//  std::shared_ptr<zbe::Value<int64_t> > vl;
//};

//int degryllmain(int, char*[]) {
//  printf("Hola Mundo!\n");
//
//  std::shared_ptr<zbe::SDLOGLWindow> window = std::make_shared<zbe::SDLOGLWindow>("Console", 50, 50, 640, 480);
//
//  auto fs = window->getFontStore();
//  auto fid = fs->loadFont("data\\fonts\\Hack-Regular.ttf", 14, {192, 192, 192, 255});
//
//  glClearColor(0, 0, 0, 0);
////  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//
//  Console c;
//
//  bool quit = false;
//  SDL_Event event;
//
//  while (!quit) {
//    window->clear();
//
//    SDL_WaitEvent(&event);
//
//    switch (event.type) {
//      case SDL_QUIT:
//        quit = true;
//        break;
//      case SDL_MOUSEWHEEL:
//        if (event.wheel.y > 0) {
//          c.lookup();
//        } else if (event.wheel.y < 0) {
//          c.lookdown();
//        }
//        break;
//      case SDL_KEYDOWN:
//        switch (event.key.keysym.sym) {
//          case SDLK_ESCAPE:
//            quit = true;
//            break;
//          case SDLK_RETURN:
//            c.execute();
//            break;
//          case SDLK_BACKSPACE:
//            c.removeglyph();
//            break;
//          case SDLK_a:
//            printf("A pulsada.\n");
//            break;
//        }
//        break;
//        case SDL_TEXTINPUT:
//          c.addutf8(event.text.text);
//          break;
//    }
//
//    int w = 0;
//    int h = 0;
//    int posy = 0;
//    for(int i = c.first(); i < c.last(); i++) {
//      SDL_Texture* texture = fs->renderText(fid, c.getLine(i).c_str());
////      SDL_Surface *surface = TTF_RenderUTF8_Shaded(font, c.getLine(i).c_str(), cf, cb);
////      SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//      SDL_QueryTexture(texture, 0, 0, &w, &h);
//      SDL_Rect dst = {0, posy, w, h};
//      window->render(texture, nullptr, &dst);
//      posy += h;
//
////      SDL_FreeSurface(surface);
//      SDL_DestroyTexture(texture);
//    }
//
//    SDL_Texture* texture = fs->renderText(fid, c.command().c_str());
////    SDL_Surface *surface = TTF_RenderUTF8_Shaded(font, c.command().c_str(), cf, cb);
////    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_QueryTexture(texture, 0, 0, &w, &h);
//    SDL_Rect dst = {0, posy, w, h};
//
//    window->render(texture, nullptr, &dst);
////    SDL_FreeSurface(surface);
//    SDL_DestroyTexture(texture);
//
//    window->present();
//  }
//
//  return (0);
//}

int degryllmain(int, char*[]) {
  const uint64_t INPUTEVENT = 1;
  const uint64_t TEXTEVENT = 2;
  std::shared_ptr<zbe::SDLOGLWindow> window = std::make_shared<zbe::SDLOGLWindow>("Console", 50, 50, 640, 480);
  auto fs = window->getFontStore();
  auto fid = fs->loadFont("data\\fonts\\Hack-Regular.ttf", 14, {192, 192, 192, 255});

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

  std::shared_ptr<zbe::InputEventGenerator> ieg = std::make_shared<zbe::InputEventGenerator>(inputBuffer, inputTextBuffer, TEXTEVENT, addText);
  std::shared_ptr<zbe::MappedInputStatusManager> ism = std::make_shared<zbe::MappedInputStatusManager>(INPUTEVENT);
  ieg->addManager(ism);

  event->addDaemon(ieg);

  auto exitv = std::make_shared<zbe::SimpleValue<int64_t> >();
  std::shared_ptr<zbe::Daemon> exitd = std::make_shared<zbe::MainLoopExit>(loop, exitv, 42);
  zbe::DaemonIH exitih(exitd);
  ism->addHandler(zbe::ZBEK_ESCAPE, &exitih);

  std::shared_ptr<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > > cavatar = std::make_shared<zbe::MBaseAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > >(console, {1, 1, 1, 1});
  auto cdl = std::make_shared<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > > >();
  cdl->push_front(cavatar);
  std::shared_ptr<zbe::Daemon> drawerDaemon = std::make_shared<zbe::BehaviorDaemon<zbe::ConsoleTextDrawer, zbe::TicketedForwardList<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > > > >(std::make_shared<zbe::ConsoleTextDrawer>(window), cdl);
  draw->addDaemon(drawerDaemon);



  loop->run();

  return 0;
}
