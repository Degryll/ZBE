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
class ZBEAPI StateLTEraserBhvFtry : virtual public Factory {
public:

  /** \brief Builds a StateMachineDaemon.
   *  \param name Name for the created StateMachineDaemon.
   *  \param cfgId StateMachineDaemon's configuration id.
   */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<int64_t> > &behaviorRsrc = RsrcStore<Behavior<int64_t> >::getInstance();
  RsrcStore<StateLTEraser> &StateLTEraserRsrc = RsrcStore<StateLTEraser>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_STATELTERASERBHVFTRY_H_
