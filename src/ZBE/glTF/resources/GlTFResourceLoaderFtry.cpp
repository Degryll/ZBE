/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GlTFResourceLoaderFtry.cpp
 * @since 2020-09-13
 * @date 2020-09-13
 * @author Ludo Degryll Batis
 * @brief Factory for GlTFResourceLoader.
 */

#include "ZBE/glTF/resources/GlTFResourceLoaderFtry.h"

namespace zbe {

void GlTFResourceLoaderFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto loader = std::make_shared<GlTFResourceLoader>();
  gltfLoaderRsrc.insert("GlTFResourceLoader."s + name, loader);
  rsrcLoaderRsrc.insert("RsrcLoader."s + name, loader);
}

void GlTFResourceLoaderFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json windowname = j["window"];
    //json extension = j["extension"];

    if(!windowname.is_string()) {
      SysError::setError("Bad config for GlTFResourceLoaderFtry - window."s + windowname.get<std::string>());
      return;
    }

    auto loader = gltfLoaderRsrc.get("GlTFResourceLoader."s + name);
    auto win = sdlWindowRsrc.get("SDLOGLWindow."s + windowname.get<std::string>());

    loader->setup(win->getTextureStore(),  win->getModelStore());

    // if(extension.is_string()) {
    //   loader->setExtension(extension.get<std::string>());
    // }

  } else {
    SysError::setError("GlTFResourceLoader config for "s + name + " not found."s);
  }
}

}  // namespace zbe
