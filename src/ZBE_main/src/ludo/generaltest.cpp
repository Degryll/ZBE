#include "ludo/generaltest.h"

#include <memory>

#include "ZBE/core/system/MainLoop.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

#include "ludo/sdlaudiotest.h"
#include "ludo/opengltest.h"

namespace ludo {

int generaltest(int, char** ) {
  using namespace zbe;
  std::shared_ptr<DaemonMaster> pre = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> post = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> event = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> common = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> react = std::make_shared<DaemonMaster>();
  std::shared_ptr<DaemonMaster> draw = std::make_shared<DaemonMaster>();
  std::shared_ptr<MainLoop> loop = std::make_shared<MainLoop>(pre, post, event, common, react, draw);


  loop->run();
  return 0;
}

} //namespace Ludo
