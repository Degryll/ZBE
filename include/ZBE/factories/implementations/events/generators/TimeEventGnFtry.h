/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventGnFtry.h
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

//  ~TimeEventGnFtry() = default;

  /** \brief Builds a TimeEventGenerators.
   *  \param name Name for the created MainLoopFtry.
   *  \param cfgId TimeEventGnFtry's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto teg = std::make_shared<TimeEventGenerator>();
    dmnRsrc.insert("Daemon."s + name, teg);
    tegRsrc.insert("TimeEventGenerator."s + name, teg);
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
  //TimeEventGenerator(int eventId, std::shared_ptr<ContextTime> contextTime = SysTime::getInstance())

      if (!(j["eventId"].type() ==json::value_t::string)){
        SysError::setError("TimeEventDaemonFtry config for "s + name + " must contain a valid string for eventId."s);
        return;
      }
      if (!(j["contextTime"].type() ==json::value_t::string)){
        SysError::setError("TimeEventDaemonFtry config for "s + name + " must contain a valid string for contexttTime."s);
        return;
      }
      std::string ename = j["eventId"].get<std::string>();
      std::string ctname = j["contextTime"].get<std::string>();

      int64_t eId = intStore.get(ename);
      auto cTime = cxTimeStore.get("ContextTime."s + ctname);

      auto teg = tegRsrc.get("TimeEventGenerator."s + name);
      teg->setEventId(static_cast<uint64_t>(eId));
      teg->setContextTime(cTime);
      teg->setStore(&store);

    } else {
      SysError::setError("TimeEventDaemonFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<TimeEventGenerator>& tegRsrc = RsrcStore<TimeEventGenerator>::getInstance();
  RsrcStore<ContextTime>& cxTimeStore = RsrcStore<ContextTime>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  EventStore& store = EventStore::getInstance();

};

} // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_GENERATORS_TIMEEVENTGNFTRY_H_
