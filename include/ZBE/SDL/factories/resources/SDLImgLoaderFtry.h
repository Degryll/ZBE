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
class SDLImgLoaderFtry : virtual public Factory {
public:

  /** \brief Builds a SDLImgLoader.
   *  \param name Name for the created SDLImgLoader.
   *  \param cfgId SDLImgLoader's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto loader = std::make_shared<SDLImgLoader>();
    sdlImgLoaderRsrc.insert("SDLImgLoader."s + name, loader);
    rsrcLoaderRsrc.insert("RsrcLoader."s + name, loader);
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
      json windowname = j["window"];
      json imgdefname = j["imgdef"];
      json extension = j["extension"];

      if(!windowname.is_string()) {
        SysError::setError("Bad config for SDLImgLoaderFtry - window."s + windowname.get<std::string>());
        return;
      }

      if(!imgdefname.is_string()) {
        SysError::setError("Bad config for SDLImgLoaderFtry - imgdef."s + imgdefname.get<std::string>());
        return;
      }

      auto loader = sdlImgLoaderRsrc.get("SDLImgLoader."s + name);
      auto sdlwin = sdlWindowRsrc.get("SDLWindow."s + windowname.get<std::string>());
      auto defLoader = rsrcDefLoaderRsrc.get("RsrcDefLoader."s + imgdefname.get<std::string>());

      loader->setImgStore(sdlwin->getImgStore());
      loader->setImgDefLoader(defLoader);

      if(extension.is_string()) {
        loader->setExtension(extension.get<std::string>());
      }

    } else {
      SysError::setError("SDLImgLoaderFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLImgLoader> &sdlImgLoaderRsrc = RsrcStore<SDLImgLoader>::getInstance();
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();
  RsrcStore<RsrcDefLoader> &rsrcDefLoaderRsrc = RsrcStore<RsrcDefLoader>::getInstance();
  RsrcStore<SDLWindow> &sdlWindowRsrc = RsrcStore<SDLWindow>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLIMGLOADERFTRY_H_
