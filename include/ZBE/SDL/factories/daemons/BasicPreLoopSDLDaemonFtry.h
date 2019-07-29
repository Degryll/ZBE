/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BasicPreLoopSDLDaemonFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for BasicPreLoopSDLDaemon.
 */

#ifndef ZBE_SDL_FACTORIES_DAEMONS_BASICPRELOOPSDLDAEMONFTRY_H_
#define ZBE_SDL_FACTORIES_DAEMONS_BASICPRELOOPSDLDAEMONFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for BasicPreLoopSDLDaemon.
 */
class ZBEAPI BasicPreLoopSDLDaemonFtry : virtual public Factory {
public:

  /** \brief Builds a BasicPreLoopSDLDaemon.
   *  \param name Name for the created BasicPreLoopSDLDaemon.
   *  \param cfgId BasicPreLoopSDLDaemon's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  //NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLWindow> &sdlWindowRsrc = RsrcStore<SDLWindow>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<BasicPreLoopSDLDaemon> &preloopRsrc = RsrcStore<BasicPreLoopSDLDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_DAEMONS_BASICPRELOOPSDLDAEMONFTRY_H_
