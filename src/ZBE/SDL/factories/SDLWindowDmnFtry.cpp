/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLWindowDmnFtry.cpp
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for Main Loop.
 */

#include "ZBE/SDL/factories/SDLWindowDmnFtry.h"

namespace zbe {

void SDLWindowDmnFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto sdlwdmn = std::make_shared<SDLWindowDaemon>();
  dmnRsrc.insert("Daemon."s + name, sdlwdmn);
  SDLWindowDmnRsrc.insert("SDLWindowDaemon."s + name, sdlwdmn);
}

void SDLWindowDmnFtry::setup(std::string name, uint64_t cfgId) {
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
      SysError::setError("Bad config for SDLWindowDmnFtry - name."s + jname.get<std::string>());
      return;
    }
    if(!title.is_string()) {
      SysError::setError("Bad config for SDLWindowDmnFtry - title."s + title.get<std::string>());
      return;
    }
    if(!x.is_string()) {
      SysError::setError("Bad config for SDLWindowDmnFtry - x."s + x.get<std::string>());
      return;
    }
    if(!y.is_string()) {
      SysError::setError("Bad config for SDLWindowDmnFtry - y."s + y.get<std::string>());
      return;
    }
    if(!w.is_string()) {
      SysError::setError("Bad config for SDLWindowDmnFtry - w."s + w.get<std::string>());
      return;
    }
    if(!h.is_string()) {
      SysError::setError("Bad config for SDLWindowDmnFtry - h."s + h.get<std::string>());
      return;
    }
    if(!wflags.is_string()) {
      SysError::setError("Bad config for SDLWindowDmnFtry - wflags."s + wflags.get<std::string>());
      return;
    }
    if(!rflags.is_string()) {
      SysError::setError("Bad config for SDLWindowDmnFtry - rflags."s + rflags.get<std::string>());
      return;
    }

    std::string aux = j["name"].get<std::string>();
    std::string cname = strStore.get(aux);
    aux = j["title"].get<std::string>();
    std::string ctitle = strStore.get(aux);
    aux = j["x"].get<std::string>();
    uint64_t cx = (uint64_t)intStore.get(aux);
    aux = j["y"].get<std::string>();
    uint64_t cy = (uint64_t)intStore.get(aux);
    aux = j["w"].get<std::string>();
    uint64_t cw = (uint64_t)intStore.get(aux);
    aux = j["h"].get<std::string>();
    uint64_t ch = (uint64_t)intStore.get(aux);
    aux = j["wflags"].get<std::string>();
    uint64_t cwflags = (uint64_t)intStore.get(aux);
    aux = j["rflags"].get<std::string>();
    uint64_t crflags = (uint64_t)intStore.get(aux);

    auto sdlwdmn = SDLWindowDmnRsrc.get("SDLWindowDaemon."s + name);
    sdlwdmn->setName(cname);
    sdlwdmn->setTitle(ctitle.c_str());
    sdlwdmn->setX(cx);
    sdlwdmn->setY(cy);
    sdlwdmn->setWidth(cw);
    sdlwdmn->setHeight(ch);
    sdlwdmn->setWindowFlags(cwflags);
    sdlwdmn->setRendererFlags(crflags);
  } else {
    SysError::setError("SDLWindowDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
