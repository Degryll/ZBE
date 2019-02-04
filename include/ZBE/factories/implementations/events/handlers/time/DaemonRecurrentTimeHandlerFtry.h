/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonRecurrentTimeHandlerFtry.h
 * @since 2019-01-31
 * @date 2019-01-31
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonRecurrentTimeHandler.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLERFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLERFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

#include "ZBE/events/handlers/time/DaemonRecurrentTimeHandler.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for DaemonRecurrentTimeHandler.
 */
class ZBEAPI DaemonRecurrentTimeHandlerFtry : virtual public Factory {
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
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<TimeEventGenerator> &tegRsrc = RsrcStore<TimeEventGenerator>::getInstance();
  RsrcStore<AvatarEntity<Avatar> > &avatarRsrc = RsrcStore<AvatarEntity<Avatar> >::getInstance();
  RsrcStore<TimeHandler> &timeRsrc = RsrcStore<TimeHandler>::getInstance();
  RsrcStore<DaemonRecurrentTimeHandler> &dmnRecurrentTimeHandlerRsrc = RsrcStore<DaemonRecurrentTimeHandler>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLERFTRY_H_
