/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLWindowFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for SDLWindow.
 */

#ifndef ZBE_SDL_FACTORIES_SDLWINDOWFTRY_H_
#define ZBE_SDL_FACTORIES_SDLWINDOWFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for SDLWindow.
 */
class SDLWindowFtry : virtual public Factory {
public:

  /** \brief Builds a SDLWindow.
   *  \param name Name for the created SDLWindow.
   *  \param cfgId SDLWindow's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto sdlwin = std::make_shared<SDLWindow>();
    sdlWindowRsrc.insert("SDLWindow."s + name, sdlwin);
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
private:
  //NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLWindow> &sdlWindowRsrc = RsrcStore<SDLWindow>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLWINDOWFTRY_H_
