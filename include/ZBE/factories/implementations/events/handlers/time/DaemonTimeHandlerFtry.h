 /**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonTimeHandlerFtry.h
 * @since 2018-12-26
 * @date 2018-12-26
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonTimeHandler.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLERFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLERFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"

#include "ZBE/events/handlers/time/DaemonTimeHandler.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for DaemonTimeHandler.
 */
class DaemonTimeHandlerFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<DaemonTimeHandler> dth = std::make_shared<DaemonTimeHandler>();
    dmnTimeHandlerRsrc.insert("DaemonTimeHandler."s + name, dth);
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
      if (!j["dmn"].is_string()) {
        SysError::setError("DaemonTimeHandlerFtry config for dmn "s + j["dmn"].get<std::string>() + ": must be a string."s);
        return;
      }
      if (!j["generator"].is_string()) {
        SysError::setError("DaemonTimeHandlerFtry config for generator "s + j["generator"].get<std::string>() + ": must be a string."s);
        return;
      }
      if (!j["time"].is_string()){
        SysError::setError("DaemonTimeHandlerFtry config for time "s + j["time"].get<std::string>() + ": must be a string."s);
        return;
      }
      std::string dname = j["dmn"].get<std::string>();
      std::string gname = j["generator"].get<std::string>();
      std::string tname = j["time"].get<std::string>();

      std::shared_ptr<Daemon> daemon = dmnRsrc.get("Daemon."s + dname);
      std::shared_ptr<TimeEventGenerator> teg = tegRsrc.get("TimeEventGenerator."s + gname);
      uint64_t time = static_cast<uint64_t>(intStore.get(tname));

      auto dth = dmnTimeHandlerRsrc.remove("DaemonTimeHandler."s + name);
      dth->setDaemon(daemon);

      teg->addAbsoluteTimer(dth, time);

    } else {
      SysError::setError("DaemonTimeHandlerFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<DaemonTimeHandler> &dmnTimeHandlerRsrc = RsrcStore<DaemonTimeHandler>::getInstance();
  RsrcStore<TimeEventGenerator> &tegRsrc = RsrcStore<TimeEventGenerator>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLERFTRY_H_
