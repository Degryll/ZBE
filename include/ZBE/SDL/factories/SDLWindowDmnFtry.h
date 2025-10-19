/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLWindowDmnFtry.h
 * @since 2019-03-20
 * @date 2019-03-20
 * @author Degryll
 * @brief Factory for SDLWindow Daemon.
 */

#ifndef ZBE_SDL_FACTORIES_SDLWINDOWDMNFTRY_H_
#define ZBE_SDL_FACTORIES_SDLWINDOWDMNFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/daemons/SDLWindowDaemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for SDLWindow Daemon.
 */
class SDLWindowDmnFtry : virtual public Factory {
public:

  /** \brief Builds a SDLWindowDaemon.
   *  \param name Name for the created SDLWindowDaemon.
   *  \param cfgId SDLWindowDaemon's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto sdlwdmn = std::make_shared<SDLWindowDaemon>();
    dmnRsrc.insert("Daemon."s + name, sdlwdmn);
    SDLWindowDmnRsrc.insert("SDLWindowDaemon."s + name, sdlwdmn);
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

private:
  //NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &dmnRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<SDLWindowDaemon> &SDLWindowDmnRsrc = RsrcStore<SDLWindowDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLWINDOWDMNFTRY_H_
