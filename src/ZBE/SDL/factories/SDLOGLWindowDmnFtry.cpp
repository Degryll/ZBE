/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLOGLWindowDmnFtry.cpp
 * @since 2019-03-25
 * @date 2019-03-25
 * @author Degryll
 * @brief Factory for SDLOGLWindow Daemon.
 */

#include "ZBE/SDL/factories/SDLOGLWindowDmnFtry.h"

namespace zbe {

void SDLOGLWindowDmnFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto sdloglwdmn = std::make_shared<SDLOGLWindowDaemon>();
  dmnRsrc.insert("Daemon."s + name, sdloglwdmn);
  SDLOGLWindowDmnRsrc.insert("SDLOGLWindowDaemon."s + name, sdloglwdmn);
}

void SDLOGLWindowDmnFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json jname = j["name"];
    json title = j["title"];
    json x = j["x"];
    json y = j["y"];
    json w = j["w"];
    json h = j["h"];
    json wflags = j["wflags"];
    json rflags = j["rflags"];
    if(!jname.is_string()) {
      SysError::setError("Bad config for SDLOGLWindowDmnFtry - name."s + jname.get<std::string>());
      return;
    }
    if(!title.is_string()) {
      SysError::setError("Bad config for SDLOGLWindowDmnFtry - title."s + title.get<std::string>());
      return;
    }
    if(!x.is_string()) {
      SysError::setError("Bad config for SDLOGLWindowDmnFtry - x."s + x.get<std::string>());
      return;
    }
    if(!y.is_string()) {
      SysError::setError("Bad config for SDLOGLWindowDmnFtry - y."s + y.get<std::string>());
      return;
    }
    if(!w.is_string()) {
      SysError::setError("Bad config for SDLOGLWindowDmnFtry - w."s + w.get<std::string>());
      return;
    }
    if(!h.is_string()) {
      SysError::setError("Bad config for SDLOGLWindowDmnFtry - h."s + h.get<std::string>());
      return;
    }
    if(!wflags.is_string()) {
      SysError::setError("Bad config for SDLOGLWindowDmnFtry - wflags."s + wflags.get<std::string>());
      return;
    }
    if(!rflags.is_string()) {
      SysError::setError("Bad config for SDLOGLWindowDmnFtry - rflags."s + rflags.get<std::string>());
      return;
    }

    std::string aux = j["name"].get<std::string>();
    std::string cname = strStore.get(aux);
    aux = j["title"].get<std::string>();
    std::string ctitle = strStore.get(aux);
    aux = j["x"].get<std::string>();
    int cx = static_cast<int>(intStore.get(aux));
    aux = j["y"].get<std::string>();
    int cy = static_cast<int>(intStore.get(aux));
    aux = j["w"].get<std::string>();
    int cw = static_cast<int>(intStore.get(aux));
    aux = j["h"].get<std::string>();
    int ch = static_cast<int>(intStore.get(aux));
    aux = j["wflags"].get<std::string>();
    Uint32 cwflags = static_cast<Uint32>(intStore.get(aux));
    aux = j["rflags"].get<std::string>();
    Uint32 crflags = static_cast<Uint32>(intStore.get(aux));

    auto sdlwdmn = SDLOGLWindowDmnRsrc.get("SDLOGLWindowDaemon."s + name);
    sdlwdmn->setName(cname);
    sdlwdmn->setTitle(ctitle.c_str());
    sdlwdmn->setX(cx);
    sdlwdmn->setY(cy);
    sdlwdmn->setWidth(cw);
    sdlwdmn->setHeight(ch);
    sdlwdmn->setWindowFlags(cwflags);
    sdlwdmn->setRendererFlags(crflags);
  } else {
    SysError::setError("SDLOGLWindowDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
