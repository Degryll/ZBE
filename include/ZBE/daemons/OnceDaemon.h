/**
 * Copyright 2015 Batis Degryll Ludo
 * @file OnceDaemon.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Degryll Ludo
 * @brief Daemon that applies a "punish" over a list of elements.
 */

#ifndef ZBE_CORE_DAEMONS_ONCEDAEMON_H_
#define ZBE_CORE_DAEMONS_ONCEDAEMON_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/system/system.h"

namespace zbe {
/** \brief Daemon that applies a "punish" over a list of elements.
 */
class OnceDaemon : public Daemon {
public:

  /** \brief Destroys the OnceDaemon.
   */
  ~OnceDaemon() = default;

  void setDaemon(std::shared_ptr<Daemon> daemon) {
    this->d = daemon;
  }

  void setTicket(std::shared_ptr<Ticket> ticket) {
    this->t = ticket;
  }

  /** \brief It will run the Daemons and deactivate it.
   */
  void run() {
    d->run();
    t->setINACTIVE();
  }

private:
  std::shared_ptr<Daemon> d;
  std::shared_ptr<Ticket> t;
};

class OnceDaemonFtry : public Factory {
public:

  /** \brief Creates a OnceDaemon from a file.
   *  \param name Name for the created OnceDaemon.
   *  \param cfgId item's configuration id.
   */
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<OnceDaemon> od = std::make_shared<OnceDaemon>();
    onceDaemonStore.insert("OnceDaemon."s + name, od);
  }

  /** \brief Set-up a OnceDaemon.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    if(cfg) {
      auto j = *cfg;
      if (!j["daemon"].is_string()) {
        SysError::setError("OnceDaemon " + name + " config for daemon must be a string."s);
        return;
      }
      if (!j["daemonMaster"].is_string()) {
        SysError::setError("OnceDaemon " + name + " config for daemonMaster must be a string."s);
        return;
      }

      std::string daemonName = j["daemon"].get<std::string>();
      auto d = daemonStore.get("daemon."+daemonName);

      std::string daemonMasterName = j["daemonMaster"].get<std::string>();
      auto dm = daemonMasterStore.get("daemonMaster."+daemonMasterName);

      auto od = onceDaemonStore.get("OnceDaemon."s + name);
      auto t = dm->addDaemon(od);

      od->setDaemon(d);
      od->setTicket(t);
    } else {
      SysError::setError("Avatar config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<OnceDaemon>& onceDaemonStore = RsrcStore<OnceDaemon>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<DaemonMaster>& daemonMasterStore = RsrcStore<DaemonMaster>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_ONCEDAEMON_H_
