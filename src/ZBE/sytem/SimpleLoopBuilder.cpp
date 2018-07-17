/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidMainGameBuilder.cpp
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid builder of the main game (the actual game, no tittle screens).
 */

#include "ZBE/system/SimpleEventDistpacher.h"

namespace zbe {

std::shared_ptr<zbe::MainLoop> SimpleEventDistpacher::build() {

  using namespace zbe;

  SDLEventDispatcher& sdlEDispatcher = SDLEventDispatcher::getInstance();
  std::shared_ptr<InputBuffer> inputBuffer = sdlEDispatcher.getInputBuffer();

  std::shared_ptr<Daemon> preLoop(new SimpleEventDistpacher());
  std::shared_ptr<DaemonMaster> postLoop(new DaemonMaster());
  std::shared_ptr<DaemonMaster> eventGenerator(new DaemonMaster());
  std::shared_ptr<DaemonMaster> commonBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> reactBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> drawMaster(new DaemonMaster());

  std::shared_ptr<MainLoop> mainLoop = std::make_shared<MainLoop>(preLoop, postLoop, eventGenerator, commonBehaviorMaster, reactBehaviorMaster, drawMaster);


  // Event generators
  std::shared_ptr<InputEventGenerator> ieg = std::make_shared<InputEventGenerator>(inputBuffer);
  std::shared_ptr<MappedInputStatusManager> ism = std::make_shared<MappedInputStatusManager>(ZBNCfg::INPUTEVENT);
  ieg->addManager(ism);
  eventGenerator->addDaemon(ieg);

  // input handlers
  ExitInputHandler* terminator = new ExitInputHandler();
  ism->addHandler(ZBEK_ESCAPE, terminator);

  return mainLoop;
}

}  // namespace zombienoid
