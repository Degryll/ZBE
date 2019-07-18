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
class ZBEAPI DaemonTimeHandlerFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<DaemonTimeHandler> &dmnTimeHandlerRsrc = RsrcStore<DaemonTimeHandler>::getInstance();
  RsrcStore<TimeEventGenerator> &tegRsrc = RsrcStore<TimeEventGenerator>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLERFTRY_H_
