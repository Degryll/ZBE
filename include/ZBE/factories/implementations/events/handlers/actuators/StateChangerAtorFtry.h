/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateChangerAtorFtry.h
 * @since 2018-12-17
 * @date 2018-12-17
 * @author Ludo Degryll Batis
 * @brief Factory for State-Changer actuators.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_STATECHANGERACTORFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_STATECHANGERACTORFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/events/handlers/Actuator.h"

#include "ZBE/events/handlers/actuators/StateChangerAtor.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for DaemonSelectorAlienAtor.
 */
template<typename T, typename R>
class StateChangerSelfAtorFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Actuator<WeakAvatarEntityContainer<Stated>,R> > &atorRsrc = RsrcStore<Actuator<WeakAvatarEntityContainer<Stated>,R> >::getInstance();
  RsrcStore<StateChangerSelfAtor<T,R> > &scsAtorRsrc = RsrcStore<StateChangerSelfAtor<T,R> >::getInstance();
  RsrcDictionary<int64_t> &intDictionary = RsrcDictionary<int64_t>::getInstance();
};

template<typename T, typename R>
void StateChangerSelfAtorFtry<T, R>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto ator = std::make_shared<StateChangerSelfAtor<T, R> >();
  uint64_t id = SysIdGenerator::getId();
  atorRsrc.insert(id, ator);
  dict.insert("Actuator."s + name, id);
  id = SysIdGenerator::getId();
  scsAtorRsrc.insert(id, ator);
  dict.insert("StateChangerSelfAtorFtry."s + name, id);
}

template<typename T, typename R>
void StateChangerSelfAtorFtry<T, R>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {

  auto j = *cfg;
    json state = j["state"];
    std::string stateName;
    if(state.is_string()){
      stateName = state.get<std::string>();
    } else {
      SysError::setError("StateChangerSelfAtorFtry state config "s + name + " is invalid or not present."s);
      return;
    }
    int64_t stateVal = intDictionary.get(stateName);
    auto ator = scsAtorRsrc.get("StateChangerSelfAtorFtry."s + name);
    ator->setNewState(stateVal);
  } else {
    SysError::setError("StateChangerSelfAtorFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_STATECHANGERACTORFTRY_H_
