/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLWindowDmnFtry.h
 * @since 2019-03-20
 * @date 2019-03-20
 * @author Degryll
 * @brief Factory for SDLWindow Daemon.
 */

#ifndef ZBE_SDL_FACTORIES_SDLWINDOWDMNFTRY_H_
#define ZBE_SDL_FACTORIES_SDLWINDOWDMNFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/daemons/SDLWindowDaemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for SDLWindow Daemon.
 */
class ZBEAPI SDLWindowDmnFtry : virtual public Factory {
public:

  /** \brief Builds a SDLWindowDaemon.
   *  \param name Name for the created SDLWindowDaemon.
   *  \param cfgId SDLWindowDaemon's configuration id.
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
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<SDLWindowDaemon> &SDLWindowDmnRsrc = RsrcStore<SDLWindowDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLWINDOWDMNFTRY_H_
