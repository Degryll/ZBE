/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLPreDrawFtry.cpp
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Ludo Degryll Batis
 * @brief Factory for OGLPreDraw.
 */


#include "ZBE/OGL/factories/daemons/OGLPreDrawFtry.h"

namespace zbe {

void OGLPreDrawFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto oglPreDraw = std::make_shared<OGLPreDrawer>();
  daemonRsrc.insert("Daemon."s + name, oglPreDraw);
  oglPreDrawRsrc.insert("OGLPreDraw."s + name, oglPreDraw);
}

void OGLPreDrawFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json window = j["window"];
    json programId = j["programId"];
    json camera = j["camera"];
    if(!window.is_string()) {
      SysError::setError("Bad config for OGLPreDrawFtry - window."s + window.get<std::string>());
      return;
    }
    if(!camera.is_string()) {
      SysError::setError("Bad config for OGLPreDrawFtry - camera."s + camera.get<std::string>());
      return;
    }
    if(!programId.is_string()) {
      SysError::setError("Bad config for OGLPreDrawFtry - program."s + programId.get<std::string>());
      return;
    }

    auto winname = window.get<std::string>();
    auto camname = camera.get<std::string>();
    auto pidName = programId.get<std::string>();

    auto win = sdloglWindowRsrc.get("SDLOGLWindow."s + winname);
    auto sdled = sdlEvenDWindowRsrc.get("SDLOGLWindow."s + winname + ".SDLEventDispatcher");
    auto cam = cameraRsrc.get("Camera."s + camname);
    auto p = uintStore.get(pidName);

    auto oglPreDraw = oglPreDrawRsrc.get("OGLPreDraw."s + name);
    oglPreDraw->setProgram(win, p);
    oglPreDraw->setCamera(cam);
    oglPreDraw->setSDLEventDispatcher(sdled);
  } else {
    SysError::setError("OGLPreDrawFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
