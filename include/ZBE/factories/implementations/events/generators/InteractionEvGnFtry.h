/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InteractionEvGnFtry.h
 * @since 2018-12-27
 * @date 2018-12-27
 * @author Ludo Degryll Batis
 * @brief Factory for InteractionEventGenerators.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_GENERATORS_INTERACTIONEVGNFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_GENERATORS_INTERACTIONEVGNFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/events/generators/InteractionEventGenerator.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for InteractionEventGenerators.
 */
template <typename R, typename IS, typename LN, typename LT>
class InteractionEvGnFtry : virtual public Factory {
public:

  /** \brief Builds a InteractionEventGenerators.
   *  \param name Name for the created MainLoopFtry.
   *  \param cfgId InteractionEvGnFtry's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  auto &uDict = RsrcDictionary<uint64_t>::getInstance();
  auto &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  auto &daemonRsrc = RsrcStore<Daemon>::getInstance();
  auto &iegRsrc = RsrcStore<InteractionEventGenerator<R, IS, LN, LT> >::getInstance();
  auto &isRsrc = RsrcStore<IS>::getInstance();
};

template <typename R, typename IS, typename LN, typename LT>
void InteractionEvGnFtry<R, IS, LN, LT>::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;

  auto ieg = std::make_shared<InteractionEventGenerator<R, IS, LN, LT> >();
  daemonRsrc.insert("Daemon."s + name, ieg);
  iegRsrc.insert("InteractionEventGenerator."s + name, ieg);
}

template <typename R, typename IS, typename LN, typename LT>
void InteractionEvGnFtry<R, IS, LN, LT>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    /*
{
"list" : "listName",
"eventId" : "valueId",
"selector" : "selectorName"
}
    */ TODO
    if (j["behavior"].type() == json::value_t::string && j["list"].type() == json::value_t::string) {
      std::string bname = j["behavior"].get<std::string>();
      std::string lname = j["list"].get<std::string>();
      uint64_t bId = dict.get("Behavior."s + bname);
      uint64_t lId = dict.get("List."s + lname);
      auto ieg = iegRsrc.get("InteractionEventGenerator."s + name);
      ieg->setPunish(behaviorRsrc.get(bId));
    } else {
      SysError::setError("BehaviorDmnFtry config for "s + name + " must contain valid strings for behavior and list names."s);
    }
  } else {
    SysError::setError("BehaviorDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_GENERATORS_INTERACTIONEVGNFTRY_H_
