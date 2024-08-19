/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLOGLWindowFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for SDLWindow.
 */

#ifndef ZBE_SDL_FACTORIES_SDLOLGWINDOWFTRY_H_
#define ZBE_SDL_FACTORIES_SDLOLGWINDOWFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

#include "ZBE/factories/Factory.h"

namespace zbe {

/** \brief Factory for SDLWindow.
 */
class ZBEAPI SDLOGLWindowFtry : virtual public Factory {
public:

  /** \brief Builds a SDLWindow.
   *  \param name Name for the created SDLWindow.
   *  \param cfgId SDLWindow's configuration id.
   */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override;

private:
  //NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLOGLWindow> &sdloglWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<SDLEventDispatcher> &sdlEvenDWindowRsrc = RsrcStore<SDLEventDispatcher>::getInstance();
  RsrcStore<InputBuffer>& ibuffRsrc = RsrcStore<InputBuffer>::getInstance();
  RsrcStore<InputTextBuffer>& itBuffRsrc = RsrcStore<InputTextBuffer>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLOLGWINDOWFTRY_H_
