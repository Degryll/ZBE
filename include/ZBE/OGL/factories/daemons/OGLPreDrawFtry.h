/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLPreDrawerFtry.h
 * @since 2020-09-22
 * @date 2020-09-22
 * @author Batis
 * @brief Factory for OGLPreDrawer
 */

#ifndef ZBE_OGL_FACTORIES_DAEMONS_OGLPREDRAWFTRY_H_
#define ZBE_OGL_FACTORIES_DAEMONS_OGLPREDRAWFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/tools/graphics/Camera.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/system.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/OGL/daemons/OGLPreDrawer.h"


namespace zbe {

/** \brief Factory for OGLPreDrawer
 */
class OGLPreDrawFtry : virtual public Factory {
public:

  /** \brief Builds a OGLPreDraw.
   *  \param name Name for the created OGLPreDraw.
   *  \param cfgId OGLPostDraw's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto oglPreDraw = std::make_shared<OGLPreDrawer>();
    daemonRsrc.insert("Daemon."s + name, oglPreDraw);
    oglPreDrawRsrc.insert("OGLPreDraw."s + name, oglPreDraw);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override{
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

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLOGLWindow> &sdloglWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<Camera> &cameraRsrc = RsrcStore<Camera>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<OGLPreDrawer> &oglPreDrawRsrc = RsrcStore<OGLPreDrawer>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<SDLEventDispatcher> &sdlEvenDWindowRsrc = RsrcStore<SDLEventDispatcher>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_OGL_FACTORIES_DAEMONS_OGLPREDRAWFTRY_H_
