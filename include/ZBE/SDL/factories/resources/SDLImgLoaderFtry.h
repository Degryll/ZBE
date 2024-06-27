/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLImgLoaderFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for SDLImgLoader.
 */

#ifndef ZBE_SDL_FACTORIES_SDLIMGLOADERFTRY_H_
#define ZBE_SDL_FACTORIES_SDLIMGLOADERFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/resources/SDLImgLoader.h"

namespace zbe {

/** \brief Factory for SDLImgLoader.
 */
class ZBEAPI SDLImgLoaderFtry : virtual public Factory {
public:

  /** \brief Builds a SDLImgLoader.
   *  \param name Name for the created SDLImgLoader.
   *  \param cfgId SDLImgLoader's configuration id.
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
  RsrcStore<SDLImgLoader> &sdlImgLoaderRsrc = RsrcStore<SDLImgLoader>::getInstance();
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();
  RsrcStore<RsrcDefLoader> &rsrcDefLoaderRsrc = RsrcStore<RsrcDefLoader>::getInstance();
  RsrcStore<SDLWindow> &sdlWindowRsrc = RsrcStore<SDLWindow>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLIMGLOADERFTRY_H_
