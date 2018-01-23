/**
 * Copyright 2012 Batis Degryll Ludo
 * @file zombienoid.cpp
 * @since 2017-12-13
 * @date 2017-12-13
 * @author degryll batis ludo
 * @brief Zombienoid main.
 */

#include "zombienoid.h"

#include <memory>

#include "zombienoid/ZBNoid.h"

namespace zombienoid {

int zombienoidmain(int, char*[]) {
  using namespace zbe;

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

  std::shared_ptr<Daemon> gameloader =  std::make_shared<ZBNoidGameLoader>(rsrcIDDic);
  std::shared_ptr<Daemon> levelloader =  std::make_shared<ZBNoidLevelLoader>(rsrcIDDic);
  //loader->run();

  std::shared_ptr<StateMachineDaemon> gameStateMachine = std::make_shared<StateMachineDaemon>(ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE), 3);
  gameStateMachine->setDaemon(MAINTITLE, titleScreen);
  gameStateMachine->setDaemon(LOADGAME, gameloader);
  gameStateMachine->setDaemon(LOADLEVEL, levelloader);
  gameStateMachine->setDaemon(MAINGAME, mainLoop);

  // (0) ZBNoidTitleBuilder title
  // (1) V ZBNoidLevelLoaderBuilder loader
  // (2) V mainLoop
  // (3) ZBNoidLevelEndBuilder end
  // (4) ZBNoidLevelClean clear

  // StateMachineDaemon stateMachine(title, loader, mainLoop, end, clear, gameStateValue)
  // stateMachine->run();

  // HUD
  // Life & point counter-----------------------------------------------------------------------------------------------------


  //mainLoop->run();
  gameStateMachine->run();

  return 0;
}
} // namespace zombieBall
