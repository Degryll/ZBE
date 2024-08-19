/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLOGLWindowDmnFtry.h
 * @since 2019-03-25
 * @date 2019-03-25
 * @author Degryll
 * @brief Factory for SDLOGLWindow Daemon.
 */

#ifndef ZBE_SDL_FACTORIES_SDLOGLWINDOWDMNFTRY_H
#define ZBE_SDL_FACTORIES_SDLOGLWINDOWDMNFTRY_H

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/daemons/SDLOGLWindowDaemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for SDLOGLWindow Daemon.
 */
class ZBEAPI SDLOGLWindowDmnFtry : virtual public Factory {
public:

  /** \brief Builds a SDLOGLWindowDaemon.
   *  \param name Name for the created SDLOGLWindowDaemon.
   *  \param cfgId SDLOGLWindowDaemon's configuration id.
   */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override;

private:
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<SDLOGLWindowDaemon> &SDLOGLWindowDmnRsrc = RsrcStore<SDLOGLWindowDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLOGLWINDOWDMNFTRY_H
