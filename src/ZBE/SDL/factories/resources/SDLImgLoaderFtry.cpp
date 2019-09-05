/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLImgLoaderFtry.cpp
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Ludo Degryll Batis
 * @brief Factory for SDLWindow.
 */

#include "ZBE/SDL/factories/resources/SDLImgLoaderFtry.h"

namespace zbe {

void SDLImgLoaderFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto loader = std::make_shared<SDLImgLoader>();
  sdlImgLoaderRsrc.insert("SDLImgLoader."s + name, loader);
}

void SDLImgLoaderFtry::setup(std::string name, uint64_t cfgId) {
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

}  // namespace zbe
