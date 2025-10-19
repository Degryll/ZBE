/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateLTEraserBhvFtry.h
 * @since 2018-11-05
 * @date 2018-11-05
 * @author Degryll
 * @brief Factory for State less than Eraser Behavior.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_STATELTERASERBHVFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_STATELTERASERBHVFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/behaviors/StateLTEraser.h"

#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for State Machine Daemons.
 */
class StateLTEraserBhvFtry : virtual public Factory {
public:

  /** \brief Builds a StateMachineDaemon.
   *  \param name Name for the created StateMachineDaemon.
   *  \param cfgId StateMachineDaemon's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<StateLTEraser> seb = std::make_shared<StateLTEraser>();
    behaviorRsrc.insert("Behavior."s + name, seb);
    StateLTEraserRsrc.insert("StateLTEraser."s + name, seb);
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
      if (j["limit"].is_string()) {
        std::string cname = j["limit"].get<std::string>();
        int64_t limit = intStore.get(cname);

        auto ss = StateLTEraserRsrc.get("StateLTEraser."s + name);
        ss->setLimit(limit);

      } else {
        SysError::setError("StateLTEraserBhvFtry config for "s + j["limit"].get<std::string>() + ": must be a string."s);
      }
    } else {
      SysError::setError("StateLTEraserBhvFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<int64_t> > &behaviorRsrc = RsrcStore<Behavior<int64_t> >::getInstance();
  RsrcStore<StateLTEraser> &StateLTEraserRsrc = RsrcStore<StateLTEraser>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_STATELTERASERBHVFTRY_H_
