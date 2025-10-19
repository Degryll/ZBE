/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleTextSDLDrawerFtry.h
 * @since 2019-03-18
 * @date 2019-03-18
 * @author Batis
 * @brief Factory for Single Text SDL Drawer
 */
//SingleTextSDLDrawer
#ifndef ZBE_SDL_FACTORIES_DRAWERS_SINGLETEXTSDLDRAWERFTRY_H_
#define ZBE_SDL_FACTORIES_DRAWERS_SINGLETEXTSDLDRAWERFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for Single Text SDL Drawer
 */
class SingleTextSDLDrawerFtry : virtual public Factory {
public:
  /** \brief Builds a SingleText SDL Drawer.
   *  \param name Name for the created SingleText SDL Drawer.
   *  \param cfgId Configuration id for the SingleText SDL Drawer.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<SingleTextSDLDrawer> ss = std::make_shared<SingleTextSDLDrawer>();
    drawerRsrc.insert("Behavior."s + name, ss);
    STSDLDrawerRsrc.insert("STSDLDrawer."s + name, ss);
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
      if (j["window"].is_string()){
      std::string windowName = j["window"].get<std::string>();
      auto w = windowRsrc.get(windowName);

      auto ssd = STSDLDrawerRsrc.get("STSDLDrawer."s + name);
      ssd->setWindow(w);

      } else {
        SysError::setError("SingleTextSDLDrawer config for "s + j["limit"].get<std::string>() + ": must be a string."s);
      }
    } else {
      SysError::setError("SingleTextSDLDrawer config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<std::string, uint64_t, Vector2D, Vector2D> >& drawerRsrc = RsrcStore<Behavior<std::string, uint64_t, Vector2D, Vector2D> >::getInstance();
  RsrcStore<SingleTextSDLDrawer>& STSDLDrawerRsrc = RsrcStore<SingleTextSDLDrawer>::getInstance();
  RsrcStore<SDLWindow>& windowRsrc = RsrcStore<SDLWindow>::getInstance();
};
}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_SDL_DRAWERS_SINGLETEXTSDLDRAWERFTRY_H_
