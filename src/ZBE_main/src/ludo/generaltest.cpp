#include "ludo/generaltest.h"

#include <memory>

#include "ZBE/core/zbe.h"

#include "ZBE/core/daemons/MainLoop.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

#include "ZBE/core/events/generators/util/InputStatusManager.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"

#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"


#include "ludo/events/handlers/LudoHandlers.h"

#include "ludo/sdlaudiotest.h"
#include "ludo/opengltest.h"

namespace ludo {
  const uint64_t INPUTEVENT = 1;

int generaltest(int, char** ) {
  using namespace zbe;
  std::shared_ptr<SDLWindow> window = std::make_shared<SDLWindow>("Ludo testing", 1000, 1000);
  Timer *sysTimer = new SDLTimer(true);
  std::shared_ptr<SysTime> sysTime = SysTime::getInstance();
  sysTime->setSystemTimer(sysTimer);
  SDLEventDispatcher& sdlEDispatcher = SDLEventDispatcher::getInstance();
  std::shared_ptr<InputBuffer> inputBuffer = sdlEDispatcher.getInputBuffer();

  std::shared_ptr<DaemonMaster> pre = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> post = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> event = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> common = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> react = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> draw = std::make_shared<DaemonMaster>();
  std::shared_ptr<MainLoop> loop = std::make_shared<MainLoop>(pre, post, event, common, react, draw);

  std::shared_ptr<Daemon> postLoopSDL = std::make_shared<BasicPostLoopSDLDaemon>(window);
  std::shared_ptr<Daemon> preLoopSDL = std::make_shared<BasicPreLoopSDLDaemon>(window);

  pre->addDaemon(preLoopSDL);
  post->addDaemon(postLoopSDL);

  std::shared_ptr<InputEventGenerator> ieg = std::make_shared<InputEventGenerator>(inputBuffer);
  std::shared_ptr<MappedInputStatusManager> ism = std::make_shared<MappedInputStatusManager>(INPUTEVENT);
  ieg->addManager(ism);

  event->addDaemon(ieg);

  ExitInputHandler* terminator = new ExitInputHandler();
  ism->addHandler(ZBEK_ESCAPE, terminator);

  loop->run();

  return 0;
}

} //namespace Ludo
