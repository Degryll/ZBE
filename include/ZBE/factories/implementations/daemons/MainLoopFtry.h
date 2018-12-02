/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MainLoopFtry.h .h
 * @since 2018-09-24
 * @date 2018-09-24
 * @author Ludo Degryll Batis
 * @brief Factory for Main Loop Daemons.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_MAINLOOPFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_MAINLOOPFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/MainLoop.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for Main Loop.
 */
class ZBEAPI MainLoopFtry : public Factory {
public:

  /** \brief Builds a MainLoop.
   *  \param name Name for the created MainLoopFtry.
   *  \param cfgId MainLoopFtry's configuration id.
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
  RsrcStore<MainLoop> &mainLoopRsrc = RsrcStore<MainLoop>::getInstance();
  RsrcStore<ContextTime> &timeRsrc = RsrcStore<ContextTime>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_MAINLOOPFTRY_H_