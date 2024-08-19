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
class ZBEAPI OGLPreDrawFtry : virtual public Factory {
public:

  /** \brief Builds a OGLPreDraw.
   *  \param name Name for the created OGLPreDraw.
   *  \param cfgId OGLPostDraw's configuration id.
   */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override;

private:
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
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
