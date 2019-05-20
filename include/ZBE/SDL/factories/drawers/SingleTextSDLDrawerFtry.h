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
class ZBEAPI SingleTextSDLDrawerFtry : virtual public Factory {
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
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<SingleTextSprite> >& drawerRsrc = RsrcStore<Behavior<SingleTextSprite> >::getInstance();
  RsrcStore<SingleTextSDLDrawer>& STSDLDrawerRsrc = RsrcStore<SingleTextSDLDrawer>::getInstance();
  RsrcStore<SDLWindow>& windowRsrc = RsrcStore<SDLWindow>::getInstance();
};
}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_SDL_DRAWERS_SINGLETEXTSDLDRAWERFTRY_H_
