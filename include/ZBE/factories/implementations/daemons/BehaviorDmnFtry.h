/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BehaviorDmnFtry.h
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for behavior daemons.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORDMNFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORDMNFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/Punishers.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for behavior daemons.
 */
template<typename L, typename ...E>
class BehaviorDmnFtry : public Factory {
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
  RsrcStore<BehaviorDaemon<L, E...> > &behaviorDmnRsrc = RsrcStore<BehaviorDaemon<L, E...> >::getInstance();
  RsrcStore<Behavior<E...> > &behaviorRsrc = RsrcStore<Behavior<E...> >::getInstance();
  RsrcStore<L> &listRsrc = RsrcStore<L>::getInstance();

};

template<typename L, typename ...E>
void BehaviorDmnFtry<L, E...>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto dm = std::make_shared<BehaviorDaemon<L, E...> >();
  uint64_t id = SysIdGenerator::getId();
  daemonRsrc.insert(id, dm);
  dict.insert("Daemon."s + name, id);
  id = SysIdGenerator::getId();
  behaviorDmnRsrc.insert(id, dm);
  dict.insert("BehaviorDaemon."s + name, id);
}

template<typename L, typename ...E>
void BehaviorDmnFtry<L, E...>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["behavior"].type() == json::value_t::string && j["list"].type() == json::value_t::string) {
      std::string bname = j["behavior"].get<std::string>();
      std::string lname = j["list"].get<std::string>();
      uint64_t bId = dict.get("Behavior."s + bname);
      uint64_t lId = dict.get("List."s + lname);
      auto dm = behaviorDmnRsrc.get("BehaviorDaemon."s + name);
      dm->setPunish(behaviorRsrc.get(bId));
      dm->setList(listRsrc.get(lId));
    } else {
      SysError::setError("BehaviorDmnFtry config for "s + name + " must contain valid strings for behavior and list names."s);
    }
  } else {
    SysError::setError("BehaviorDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORDMNFTRY_H_
