/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLModelSheetDrawerFtry.h
 * @since 2019-06-05
 * @date 2019-06-05
 * @author Batis
 * @brief Factory for Single OGL Model Sheet Drawer
 */

#ifndef ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWERFTRY_H_
#define ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWERFTRY_H_

#include <string>


#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/OGL/graphics/implementations/OGLModelSheets.h"
#include "ZBE/OGL/drawers/OGLModelSheetDrawer.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for Single Text SDL Drawer
 */
template<unsigned idx, typename T, typename ...Ts>
class OGLModelSheetDrawerFtry : virtual public Factory {
public:
  /** \brief Builds a SingleText SDL Drawer.
   *  \param name Name for the created SingleText SDL Drawer.
   *  \param cfgId Configuration id for the SingleText SDL Drawer.
   */
   void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>:: getInstance();
  RsrcStore<Behavior<T, Ts...> >& drawerRsrc = RsrcStore<Behavior<T, Ts...> >::getInstance();
  RsrcStore<OGLModelSheetDrawer<idx, T, Ts...> >& oGLMSDrawerRsrc = RsrcStore<OGLModelSheetDrawer<idx, T, Ts...> >::getInstance();
  RsrcStore<SDLOGLWindow>& windowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
};

template<unsigned idx, typename T, typename ...Ts>
void OGLModelSheetDrawerFtry<idx, T, Ts...>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  std::shared_ptr<OGLModelSheetDrawer<idx, T, Ts...> > ss = std::make_shared<OGLModelSheetDrawer<idx, T, Ts...> >();
  drawerRsrc.insert("Behavior."s + name, ss);
  oGLMSDrawerRsrc.insert("OGLMSDrawer."s + name, ss);
}

template<unsigned idx, typename T, typename ...Ts>
void OGLModelSheetDrawerFtry<idx, T, Ts...>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["window"].is_string()){
     std::string windowName = j["window"].get<std::string>();
     auto w = windowRsrc.get("SDLOGLWindow."s + windowName);
       if (j["programId"].is_string()){
         std::string pidName = j["programId"].get<std::string>();
         auto p = uintStore.get(pidName);
         auto ssd = oGLMSDrawerRsrc.get("OGLMSDrawer."s + name);
         ssd->setConfig(w, p);
       } else {
         SysError::setError("OGLModelSheetDrawer config for programId must be a string."s);
       }
    } else {
      SysError::setError("OGLModelSheetDrawer config for window: "s + j["window"].get<std::string>() + ": must be a string."s);
    }
  } else {
    SysError::setError("OGLModelSheetDrawer config for "s + name + " not found."s);
  }
}

}  // namespace zbe

#endif  // ZBE_OGL_DRAWERS_OGLMODELSHEETSDLDRAWERFTRY_H_
