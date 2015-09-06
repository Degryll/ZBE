#ifndef CORE_DAEMONS_DAEMONMASTER_H
#define CORE_DAEMONS_DAEMONMASTER_H

#include <vector>
#include "./Daemon.h"

namespace zbe {
class DaemonMaster : public Daemon {
  public:
    DaemonMaster();
    virtual ~DaemonMaster();

    void run();

    void addDaemon(Daemon * daemon);

  private:
    std::vector<Daemon> * daemonList;
};

}

#endif // CORE_DAEMONS_DAEMONMASTER_H
