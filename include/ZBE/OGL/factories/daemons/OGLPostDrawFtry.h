/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLPostDrawFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for OGLPostDraw.
 */

#ifndef ZBE_OGL_FACTORIES_DAEMONS_OGLPOSTDRAWFTRY_H_
#define ZBE_OGL_FACTORIES_DAEMONS_OGLPOSTDRAWFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/system.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/OGL/daemons/OGLPostDraw.h"

namespace zbe {

/** \brief Factory for BasicPostLoopSDLDaemonFtry.
 */
class ZBEAPI OGLPostDrawFtry : virtual public Factory {
public:

  /** \brief Builds a OGLPostDraw.
   *  \param name Name for the created OGLPostDraw.
   *  \param cfgId OGLPostDraw's configuration id.
   */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLOGLWindow> &sdloglWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<OGLPostDraw> &oglPostDrawRsrc = RsrcStore<OGLPostDraw>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_OGL_FACTORIES_DAEMONS_OGLPOSTDRAWFTRY_H_
