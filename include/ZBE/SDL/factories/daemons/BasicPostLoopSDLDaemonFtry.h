/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BasicPostLoopSDLDaemonFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for BasicPostLoopSDLDaemon.
 */

#ifndef ZBE_SDL_FACTORIES_DAEMONS_BASICPOSTLOOPSDLDAEMONFTRY_H_
#define ZBE_SDL_FACTORIES_DAEMONS_BASICPOSTLOOPSDLDAEMONFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for BasicPostLoopSDLDaemonFtry.
 */
class ZBEAPI BasicPostLoopSDLDaemonFtry : virtual public Factory {
public:

  /** \brief Builds a BasicPostLoopSDLDaemon.
   *  \param name Name for the created BasicPostLoopSDLDaemon.
   *  \param cfgId BasicPostLoopSDLDaemon's configuration id.
   */
  void create(std::string name, uint64_t) override;

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
  RsrcStore<BasicPostLoopSDLDaemon> &postloopRsrc = RsrcStore<BasicPostLoopSDLDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_DAEMONS_BASICPOSTLOOPSDLDAEMONFTRY_H_
