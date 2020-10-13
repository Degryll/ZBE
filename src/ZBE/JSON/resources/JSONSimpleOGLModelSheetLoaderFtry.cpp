/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONSimpleOGLModelSheetLoaderFtry.cpp
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Ludo Degryll Batis
 * @brief Factory for JSONSimpleOGLModelSheetLoader.
 */

#include "ZBE/JSON/resources/JSONSimpleOGLModelSheetLoaderFtry.h"

namespace zbe {

void JSONSimpleOGLModelSheetLoaderFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto jsoglmsl = std::make_shared<JSONSimpleOGLModelSheetLoader>();
  rsrclRsrc.insert("RsrcLoader."s + name, jsoglmsl);
  jsoglmslRsrc.insert("JSONSimpleOGLModelSheetLoader."s + name, jsoglmsl);
}

void JSONSimpleOGLModelSheetLoaderFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json window = j["window"];
    if(!window.is_string()) {
      SysError::setError("Bad config for JSONSimpleOGLModelSheetLoaderFtry - window."s + window.get<std::string>());
      return;
    }

    auto winname = j["window"].get<std::string>();
    auto win = sdlOGLWindowRsrc.get("SDLOGLWindow."s + winname);

    auto jsoglmsl = jsoglmslRsrc.get("JSONSimpleOGLModelSheetLoader."s + name);
    jsoglmsl->setWindow(win);
  } else {
    SysError::setError("JSONSimpleOGLModelSheetLoaderFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
