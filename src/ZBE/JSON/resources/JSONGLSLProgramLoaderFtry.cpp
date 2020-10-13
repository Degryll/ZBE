/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONGLSLProgramLoaderFtry.cpp
 * @since 2020-09-16
 * @date 2020-09-16
 * @author Ludo Degryll Batis
 * @brief Factory for JSONSimpleOGLModelSheetLoader.
 */

#include "ZBE/JSON/resources/JSONGLSLProgramLoaderFtry.h"

namespace zbe {

void JSONGLSLProgramLoaderFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto jsoglmsl = std::make_shared<JSONGLSLProgramLoader>();
  rsrclRsrc.insert("RsrcLoader."s + name, jsoglmsl);
  jsonglslplRsrc.insert("JSONGLSLProgramLoader."s + name, jsoglmsl);
}

void JSONGLSLProgramLoaderFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json window = j["window"];
    if(!window.is_string()) {
      SysError::setError("Bad config for JSONGLSLProgramLoaderFtry - window."s + window.get<std::string>());
      return;
    }

    auto winname = j["window"].get<std::string>();
    auto win = sdlOGLWindowRsrc.get("SDLOGLWindow."s + winname);

    auto jsglslpl = jsonglslplRsrc.get("JSONGLSLProgramLoader."s + name);
    jsglslpl->setWindow(win);
  } else {
    SysError::setError("JSONGLSLProgramLoaderFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
