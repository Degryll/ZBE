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
class ZBEAPI StateSetterBhvFtry : public Factory {
public:

  /** \brief Builds a StateMachineDaemon.
   *  \param name Name for the created StateMachineDaemon.
   *  \param cfgId StateMachineDaemon's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<Stated> > &behaviorRsrc = RsrcStore<Behavior<Stated> >::getInstance();
  RsrcStore<StateSetter> &StateSetterRsrc = RsrcStore<StateSetter>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_STATESETTERBHVFTRY_H_
