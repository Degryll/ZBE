/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BehaviorDmnFtry.h
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for behavior daemons.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_DMNSELECTORATORFCTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_DMNSELECTORATORFCTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/events/handlers/Actuator.h"

#include "ZBE/events/handlers/actuators/DaemonSelectorAtor.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for behavior daemons.
 */
template<typename T, typename R>
class DaemonSelectorAlienAtorFtry : public Factory {
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
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Actuator<T,R> > &atorRsrc = RsrcStore<Actuator<T,R> >::getInstance();
  RsrcStore<DaemonSelectorAlienAtor<T,R> > &dsalAtorRsrc = RsrcStore<DaemonSelectorAlienAtor<T,R> >::getInstance();
};

template<typename T, typename R>
void DaemonSelectorAlienAtorFtry<T, R>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto ator = std::make_shared<DaemonSelectorAlienAtor<T, R> >();
  uint64_t id = SysIdGenerator::getId();
  atorRsrc.insert(id, ator);
  dict.insert("Actuator."s + name, id);
  id = SysIdGenerator::getId();
  dsalAtorRsrc.insert(id, ator);
  dict.insert("DaemonSelectorAlienAtor."s + name, id);
}

template<typename T, typename R>
void DaemonSelectorAlienAtorFtry<T, R>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json daemons = j["daemons"];
    auto dsaa = dsalAtorRsrc.get("DaemonSelectorAlienAtor."s + name);
    for (auto dmn : daemons) {
      if (dmn[0].is_string() && dmn[1].is_string()) {
        std::string dname = dmn[0].get<std::string>();
        std::string sname = dmn[1].get<std::string>();
        uint64_t stateno = dict.get("State."s + sname);
        uint64_t dId = dict.get("Daemon."s + dname);
        dsaa->setDaemon(stateno, daemonRsrc.get(dId));
      } else {
        SysError::setError("StateMachineDmnFtry config for "s + dmn[0].get<std::string>() + ": state is not an integer."s);
      }
    }

  } else {
    SysError::setError("DaemonSelectorAlienAtorFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_DMNSELECTORATORFCTRY_H_
