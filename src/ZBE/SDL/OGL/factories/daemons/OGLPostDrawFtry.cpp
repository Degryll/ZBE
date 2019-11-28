/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLPostDrawFtry.cpp
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Ludo Degryll Batis
 * @brief Factory for OGLPostDraw.
 */

#include "ZBE/OGL/factories/daemons/OGLPostDrawFtry.h"

namespace zbe {

void OGLPostDrawFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto oglPostDraw = std::make_shared<OGLPostDraw>();
  daemonRsrc.insert("Daemon."s + name, oglPostDraw);
  oglPostDrawRsrc.insert("OGLPostDraw."s + name, oglPostDraw);
}

void OGLPostDrawFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json window = j["window"];
    if(!window.is_string()) {
      SysError::setError("Bad config for OGLPostDrawFtry - window."s + window.get<std::string>());
      return;
    }

    auto winname = j["window"].get<std::string>();
    auto win = sdloglWindowRsrc.get("SDLOGLWindow."s + winname);

    auto oglPostDraw = oglPostDrawRsrc.get("OGLPostDraw."s + name);
    oglPostDraw->setWindow(win);
  } else {
    SysError::setError("OGLPostDrawFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
