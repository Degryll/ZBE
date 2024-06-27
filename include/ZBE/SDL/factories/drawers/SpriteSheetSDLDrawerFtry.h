/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SpriteSheetSDLDrawerFtry.h
 * @since 2019-03-18
 * @date 2019-03-18
 * @author Batis
 * @brief Factory for Sprite Sheet SDL Drawer
 */

#ifndef ZBE_SDL_FACTORIES_DRAWERS_SPRITESHEETSDLDRAWER_H_
#define ZBE_SDL_FACTORIES_DRAWERS_SPRITESHEETSDLDRAWER_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

//window(window), imgStore(window->getImgStore()), rmss(RsrcStore<SpriteSheet<T> >::getInstance())
namespace zbe {

/** \brief Factory for Sprite Sheet SDL Drawer
 */
template<unsigned gidIdx, typename T, typename ...Ts>
class SpriteSheetSDLDrawerFtry : virtual public Factory {
public:
  /** \brief Builds a SpriteSheet SDL Drawer.
   *  \param name Name for the created SpriteSheet SDL Drawer.
   *  \param cfgId Configuration id for the SpriteSheet SDL Drawer.
   */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<T, Ts...> >& drawerRsrc = RsrcStore<Behavior<T, Ts...> >::getInstance();
  RsrcStore<SpriteSheetSDLDrawer<gidIdx, T, Ts...> >& SSSDLDrawerRsrc = RsrcStore<SpriteSheetSDLDrawer<gidIdx, T, Ts...> >::getInstance();
  RsrcStore<SDLWindow>& windowRsrc = RsrcStore<SDLWindow>::getInstance();
};

template<unsigned gidIdx, typename T, typename ...Ts>
void SpriteSheetSDLDrawerFtry<gidIdx, T, Ts...>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  std::shared_ptr<SpriteSheetSDLDrawer<gidIdx, T, Ts...> > ss = std::make_shared<SpriteSheetSDLDrawer<gidIdx, T, Ts...> >();
  drawerRsrc.insert("Behavior."s + name, ss);
  SSSDLDrawerRsrc.insert("SSSDLDrawer."s + name, ss);
}

template<unsigned gidIdx, typename T, typename ...Ts>
void SpriteSheetSDLDrawerFtry<gidIdx, T, Ts...>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["window"].is_string()){
      std::string windowName = j["window"].get<std::string>();
      auto w = windowRsrc.get("SDLWindow."s + windowName);

      auto ssd = SSSDLDrawerRsrc.get("SSSDLDrawer."s + name);
      ssd->setWindow(w);

    } else {
      SysError::setError("SpriteSheetSDLDrawer config for "s + j["limit"].get<std::string>() + ": must be a string."s);
    }
  } else {
    SysError::setError("SpriteSheetSDLDrawer config for "s + name + " not found."s);
  }
}

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_
