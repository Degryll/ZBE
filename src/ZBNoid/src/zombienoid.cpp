/**
 * Copyright 2012 Batis Degryll Ludo
 * @file zombienoid.cpp
 * @since 2017-12-13
 * @date 2017-12-13
 * @author degryll batis ludo
 * @brief Zombienoid main.
 */

//#include "zombienoid.h"

#include <memory>

#include "ZBNoid.h"

int main(int, char*[]) {
  using namespace zbe;
  using namespace zombienoid;

  ZBNCfg::initIds();

  std::shared_ptr<RsrcIDDictionary> rsrcIDDic = std::make_shared<RsrcIDDictionary>(RSRC_ID_DICT_SIZE);
  std::shared_ptr<SDLWindow> window = std::make_shared<SDLWindow>(ZBENOID_WINDOW_TITLE, WIDTH, HEIGHT);
  Timer *sysTimer = new SDLTimer(true);
  SysTime &sysTime = SysTime::getInstance();
  sysTime.setSystemTimer(sysTimer);
  SDLEventDispatcher& sdlEDispatcher = SDLEventDispatcher::getInstance();
  std::shared_ptr<InputBuffer> inputBuffer = sdlEDispatcher.getInputBuffer();

  ZBNoidResourceLoader resourceLoader(rsrcIDDic, window->getImgStore(), window->getFontStore());
  resourceLoader.run();

  ZBNoidMainGameBuilder maingameBuilder(rsrcIDDic, window, inputBuffer);
  std::shared_ptr<Daemon> mainLoop = maingameBuilder.build();

  ZBNoidTitleBuilder titleBuilder(rsrcIDDic, window, inputBuffer);
  std::shared_ptr<Daemon> titleScreen = titleBuilder.build();

  ZBNoidWinScreenBuilder winScreenBuilder(rsrcIDDic, window, inputBuffer);
  std::shared_ptr<Daemon> winScreen = winScreenBuilder.build();

  ZBNoidLostScreenBuilder lostScreenBuilder(rsrcIDDic, window, inputBuffer);
  std::shared_ptr<Daemon> lostScreen = lostScreenBuilder.build();

  std::shared_ptr<Daemon> gameLoader =  std::make_shared<ZBNoidGameLoader>(rsrcIDDic);
  std::shared_ptr<Daemon> levelLoader =  std::make_shared<ZBNoidLevelLoader>(rsrcIDDic);
  std::shared_ptr<Daemon> levelCleaner =  std::make_shared<ZBNoidLevelCleaner>();
  std::shared_ptr<Daemon> levelReset =  std::make_shared<ZBNoidLevelReset>();

  std::shared_ptr<StateMachineDaemon> gameStateMachine = std::make_shared<StateMachineDaemon>(ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE), 3);
  gameStateMachine->setDaemon(LOADGAME, gameLoader);
  gameStateMachine->setDaemon(MAINTITLE, titleScreen);
  gameStateMachine->setDaemon(GAMERESET, levelReset);
  gameStateMachine->setDaemon(LOADLEVEL, levelLoader);
  gameStateMachine->setDaemon(MAINGAME, mainLoop);
  gameStateMachine->setDaemon(WINENDGAME, winScreen);
  gameStateMachine->setDaemon(LOSTENDGAME, lostScreen);
  gameStateMachine->setDaemon(CLEARGAME, levelCleaner);

  // LOADGAME = 0,
  // MAINTITLE = 1,
  // GAMERESET = 2,
  // LOADLEVEL = 3,
  // MAINGAME = 4,
  // LOSTENDGAME = 5,
  // WINENDGAME = 6,
  // CLEARGAME = 7,
  // EXIT = -1,

  // HUD
  // Life & point counter-----------------------------------------------------------------------------------------------------

  //mainLoop->run();
  gameStateMachine->run();

  return 0;
}
