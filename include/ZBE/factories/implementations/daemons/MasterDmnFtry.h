/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MasterDmnFtry.h
 * @since 2018-09-05
 * @date 2018-09-05
 * @author Ludo Degryll Batis
 * @brief Factory for Daemon Masters.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_MASTERDMNFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_MASTERDMNFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for Master Daemons.
 */
class MasterDmnFtry : public Factory {
public:

  /** \brief Builds a MasterDmnFtry.
   *  \param name Name for the created MasterDmnFtry.
   *  \param cfgId MasterDmnFtry's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<DaemonMaster> dm = std::make_shared<DaemonMaster>();

    uint64_t id = SysIdGenerator::getId();
    daemonRsrc.insert(id, dm);
    dict.insert("Daemon."s + name, id);
    id = SysIdGenerator::getId();
    dmnMasterRsrc.insert(id, dm);
    dict.insert("DaemonMaster."s + name, id);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      auto dm = dmnMasterRsrc.get("DaemonMaster."s + name);

      json daemons = j["daemons"];
      for (auto daemon = daemons.rbegin(); daemon != daemons.rend(); ++daemon) {
        if (daemon->is_string()) {
          uint64_t dId = dict.get("Daemon."s + daemon->get<std::string>());
          auto ticket = dm->addDaemon(daemonRsrc.get(dId));
          ticketRsrc.insert(name + "."s + daemon->get<std::string>() + ".ticket"s, ticket);
        } else {
          SysError::setError("MasterDmnFtry config for "s + name + " not valid."s);
        }
      }

      daemons = j["disabledDaemons"];
      for (auto daemon : daemons) {
        if (daemon.is_string()) {
          uint64_t dId = dict.get("Daemon."s + daemon.get<std::string>());
          auto ticket = dm->addDaemon(daemonRsrc.get(dId));
          ticketRsrc.insert(name+"."s + daemon.get<std::string>() + ".ticket"s, ticket);
          ticket->setINACTIVE();
        } else {
          SysError::setError("MasterDmnFtry config for "s + name + " (disabled) not valid."s);
        }
      }
    } else {
      SysError::setError("MasterDmnFtry config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<DaemonMaster> &dmnMasterRsrc = RsrcStore<DaemonMaster>::getInstance();
  RsrcStore<Ticket> &ticketRsrc = RsrcStore<Ticket>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_MASTERDMNFTRY_H_
