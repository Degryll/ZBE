/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateSetterBhvFtry.h
 * @since 2018-12-13
 * @date 2018-12-13
 * @author Degryll
 * @brief Factory for State Setter Behavior.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_STATESETTERBHVFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_STATESETTERBHVFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/behaviors/StateSetter.h"

#include "ZBE/entities/avatars/Stated.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for State Machine Daemons.
 */
class StateSetterBhvFtry : virtual public Factory {
public:

  /** \brief Builds a StateMachineDaemon.
   *  \param name Name for the created StateMachineDaemon.
   *  \param cfgId StateMachineDaemon's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<StateSetter> ss = std::make_shared<StateSetter>();
    behaviorRsrc.insert("Behavior."s + name, ss);
    StateSetterRsrc.insert("StateSetter."s + name, ss);
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
      if (j["state"].is_string()) {
        std::string cname = j["state"].get<std::string>();
        int64_t state = intStore.get(cname);

        auto ss = StateSetterRsrc.get("StateSetter."s + name);
        ss->setState(state);

      } else {
        SysError::setError("StateSetterBhvFtry config for "s + j["state"].get<std::string>() + ": must be a string."s);
      }
    } else {
      SysError::setError("StateSetterBhvFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<int64_t> > &behaviorRsrc = RsrcStore<Behavior<int64_t> >::getInstance();
  RsrcStore<StateSetter> &StateSetterRsrc = RsrcStore<StateSetter>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_STATESETTERBHVFTRY_H_
