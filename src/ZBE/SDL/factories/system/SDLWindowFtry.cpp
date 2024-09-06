/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLWindowFtry.cpp
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Ludo Degryll Batis
 * @brief Factory for SDLWindow.
 */

#include "ZBE/SDL/factories/system/SDLWindowFtry.h"

namespace zbe {

void SDLWindowFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto sdlwin = std::make_shared<SDLWindow>();
  sdlWindowRsrc.insert("SDLWindow."s + name, sdlwin);
}

void SDLWindowFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json title = j["title"];
    json x = j["x"];
    json y = j["y"];
    json w = j["w"];
    json h = j["h"];
    json wflags = j["wflags"];
    json rflags = j["rflags"];
    if(!title.is_string()) {
      SysError::setError("Bad config for SDLWindowFtry - title."s + title.get<std::string>());
      return;
    }
    if(!x.is_string()) {
      SysError::setError("Bad config for SDLWindowFtry - x."s + x.get<std::string>());
      return;
    }
    if(!y.is_string()) {
      SysError::setError("Bad config for SDLWindowFtry - y."s + y.get<std::string>());
      return;
    }
    if(!w.is_string()) {
      SysError::setError("Bad config for SDLWindowFtry - w."s + w.get<std::string>());
      return;
    }
    if(!h.is_string()) {
      SysError::setError("Bad config for SDLWindowFtry - h."s + h.get<std::string>());
      return;
    }
    if(!wflags.is_string()) {
      SysError::setError("Bad config for SDLWindowFtry - wflags."s + wflags.get<std::string>());
      return;
    }
    if(!rflags.is_string()) {
      SysError::setError("Bad config for SDLWindowFtry - rflags."s + rflags.get<std::string>());
      return;
    }

    auto aux = j["title"].get<std::string>();
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

    auto sdlwin = sdlWindowRsrc.get("SDLWindow."s + name);
    sdlwin->setTitle(ctitle.c_str());
    sdlwin->setX(cx);
    sdlwin->setY(cy);
    sdlwin->setWidth(cw);
    sdlwin->setHeight(ch);
    sdlwin->setWindow_flags(cwflags);
    sdlwin->setRenderer_flags(crflags);
    sdlwin->run();
  } else {
    SysError::setError("SDLWindowFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
