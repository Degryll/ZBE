/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLOGLWindowFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for SDLWindow.
 */

#ifndef ZBE_SDL_FACTORIES_SDLOLGWINDOWFTRY_H_
#define ZBE_SDL_FACTORIES_SDLOLGWINDOWFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

#include "ZBE/factories/Factory.h"

namespace zbe {

/** \brief Factory for SDLWindow.
 */
class SDLOGLWindowFtry : virtual public Factory {
public:

  /** \brief Builds a SDLWindow.
   *  \param name Name for the created SDLWindow.
   *  \param cfgId SDLWindow's configuration id.
   */
  void create(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;

    auto sdlwin = std::make_shared<SDLOGLWindow>();
    sdloglWindowRsrc.insert("SDLOGLWindow."s + name, sdlwin);

    auto ib = std::make_shared<InputBuffer>();
    ibuffRsrc.insert("SDLOGLWindow."s + name + ".InputBuffer", ib);

    auto itb = std::make_shared<InputTextBuffer>();
    itBuffRsrc.insert("SDLOGLWindow."s + name + ".InputTextBuffer", itb);

    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json eventDispatcher = j["eventdispatcher"];
      if(eventDispatcher.is_string()) {
        // TODO traerse el event distpatcher de la config
        // TODO Naming de espacios de nombres aquí, que es un poco raro
        auto sdlED = sdlEvenDWindowRsrc.get("SDLEventDispatcher."s + eventDispatcher.get<std::string>());
        sdlEvenDWindowRsrc.insert("SDLOGLWindow."s + name + ".SDLEventDispatcher", sdlED);  
      } else {
        auto sdlED = std::make_shared<SDLEventDispatcher>();
        sdlEvenDWindowRsrc.insert("SDLOGLWindow."s + name + ".SDLEventDispatcher", sdlED);
      }
    } else {
      SysError::setError("SDLOGLWindowFtry config for "s + name + " not found."s);
    }
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
      auto sdloglwin = sdloglWindowRsrc.get("SDLOGLWindow."s + name);
      configure(cfg, sdloglwin);
    } else {
      SysError::setError("SDLOGLWindowFtry config for "s + name + " not found."s);
    }
  }

  void configure(std::shared_ptr<nlohmann::json> cfg, std::shared_ptr<SDLOGLWindow> window, std::string factoryName = "SDLOGLWindowFtry") {
    using namespace std::string_literals;
    using namespace nlohmann;
    auto j = *cfg;
    json title = j["title"];
    json x = j["x"];
    json y = j["y"];
    json w = j["w"];
    json h = j["h"];
    json wflags = j["wflags"];
    json rflags = j["rflags"];
    if(!title.is_string()) {
      SysError::setError("Bad config for " + factoryName + " - title."s + title.get<std::string>());
      return;
    }
    if(!x.is_string()) {
      SysError::setError("Bad config for " + factoryName + " - x."s + x.get<std::string>());
      return;
    }
    if(!y.is_string()) {
      SysError::setError("Bad config for " + factoryName + " - y."s + y.get<std::string>());
      return;
    }
    if(!w.is_string()) {
      SysError::setError("Bad config for " + factoryName + " - w."s + w.get<std::string>());
      return;
    }
    if(!h.is_string()) {
      SysError::setError("Bad config for " + factoryName + " - h."s + h.get<std::string>());
      return;
    }
    if(!wflags.is_string()) {
      SysError::setError("Bad config for " + factoryName + " - wflags."s + wflags.get<std::string>());
      return;
    }
    if(!rflags.is_string()) {
      SysError::setError("Bad config for " + factoryName + " - rflags."s + rflags.get<std::string>());
      return;
    }

    auto aux = j["title"].get<std::string>();
    std::string ctitle = strStore.get(aux);
    aux = j["x"].get<std::string>();
    int cx =  static_cast<int>(intStore.get(aux));
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

    window->setTitle(ctitle.c_str());
    window->setX(cx);
    window->setY(cy);
    window->setWidth(cw);
    window->setHeight(ch);
    window->setWindow_flags(cwflags);
    window->setRenderer_flags(crflags);
    window->setDict(&dict);
    window->run();
  }

private:
  //NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLOGLWindow> &sdloglWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<SDLEventDispatcher> &sdlEvenDWindowRsrc = RsrcStore<SDLEventDispatcher>::getInstance();
  RsrcStore<InputBuffer>& ibuffRsrc = RsrcStore<InputBuffer>::getInstance();
  RsrcStore<InputTextBuffer>& itBuffRsrc = RsrcStore<InputTextBuffer>::getInstance();
  NameRsrcDictionary& dict = NameRsrcDictionary::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLOLGWINDOWFTRY_H_
