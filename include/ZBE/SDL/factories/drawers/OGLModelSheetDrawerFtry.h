/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLModelSheetDrawerFtry.h
 * @since 2019-06-05
 * @date 2019-06-05
 * @author Batis
 * @brief Factory for Single OGL Model Sheet Drawer
 */

#ifndef ZBE_SDL_FACTORIES_DRAWERS_OGLMODELSHEETDRAWERFTRY_H_
#define ZBE_SDL_FACTORIES_DRAWERS_OGLMODELSHEETDRAWERFTRY_H_

#include <string>

#include <GL/glew.h>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/OGL/graphics/implementations/SingleModelOGLModelSheet.h"
#include "ZBE/OGL/drawers/OGLModelSheetDrawer.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for Single Text SDL Drawer
 */
template<typename T>
class OGLModelSheetDrawerFtry : virtual public Factory {
public:
  /** \brief Builds a SingleText SDL Drawer.
   *  \param name Name for the created SingleText SDL Drawer.
   *  \param cfgId Configuration id for the SingleText SDL Drawer.
   */
   void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>:: getInstance();
  RsrcStore<Behavior<T> >& drawerRsrc = RsrcStore<Behavior<T> >::getInstance();
  RsrcStore<OGLModelSheetDrawer<T> >& oGLMSDrawerRsrc = RsrcStore<OGLModelSheetDrawer<T> >::getInstance();
  RsrcStore<SDLOGLWindow>& windowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
};

template<typename T>
void OGLModelSheetDrawerFtry<T>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  std::shared_ptr<OGLModelSheetDrawer<T> > ss = std::make_shared<OGLModelSheetDrawer<T> >();
  drawerRsrc.insert("Drawer."s + name, ss);
  oGLMSDrawerRsrc.insert("OGLMSDrawer."s + name, ss);
}

template<typename T>
void OGLModelSheetDrawerFtry<T>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  std::shared_ptr<SDLOGLWindow> w;
  uint64_t p;

  if(cfg) {
    auto j = *cfg;
    if (j["window"].is_string()){
     std::string windowName = j["window"].get<std::string>();
     w = windowRsrc.get(windowName);
    } else {
      SysError::setError("OGLModelSheetDrawer config for window: "s + j["window"].get<std::string>() + ": must be a string."s);
    }
    if (j["programId"].is_string()){
      std::string pidName = j["programId"].get<std::string>();
      p = (uint64_t)intStore.get(pidName);

      auto ssd = oGLMSDrawerRsrc.get("OGLMSDrawer."s + name);
      ssd->setConfig(w, p);
    } else {
      SysError::setError("OGLModelSheetDrawer config for programId: "s + j["programId"].get<std::string>() + ": must be a string."s);
    }

  } else {
    SysError::setError("OGLModelSheetDrawer config for "s + name + " not found."s);
  }
}

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_SDL_DRAWERS_OGLMODELSHEETDRAWERFTRY_H_
