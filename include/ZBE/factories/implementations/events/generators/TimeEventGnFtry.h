/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InteractionEvGnFtry.h
 * @since 2019-07-01
 * @date 2019-07-01
 * @author Ludo Degryll Batis
 * @brief Factory for TimeEventGenerators.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_GENERATORS_TIMEEVENTGNFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_GENERATORS_TIMEEVENTGNFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/tools/time/ContextTime.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/events/generators/TimeEventGenerator.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for TimeEventGenerators.
 */
class TimeEventGnFtry : virtual public Factory {
public:

  /** \brief Builds a TimeEventGenerators.
   *  \param name Name for the created MainLoopFtry.
   *  \param cfgId TimeEventGnFtry's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<TimeEventGenerator>& tegRsrc = RsrcStore<TimeEventGenerator>::getInstance();
  RsrcStore<ContextTime>& cxTimeStore = RsrcStore<ContextTime>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();

};

} // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_GENERATORS_TIMEEVENTGNFTRY_H_
