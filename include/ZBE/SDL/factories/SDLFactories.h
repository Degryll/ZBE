/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CommonFactories.h
 * @since 2019-02-20
 * @date 2019-02-20
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all common factories.
 */

#ifndef ZBE_SDL_FACTORIES_SDLFACTORIES_H_
#define ZBE_SDL_FACTORIES_SDLFACTORIES_H_

#include <string>

#include "ZBE/factories/Factory.h"

#include "ZBE/SDL/factories/system/SDLWindowFtry.h"
#include "ZBE/SDL/factories/system/SDLOGLWindowFtry.h"
#include "ZBE/SDL/factories/resources/SDLImgLoaderFtry.h"
#include "ZBE/OGL/resources/OGLImgLoader.h"
#include "ZBE/SDL/factories/system/SDLSysTimeFtry.h"
#include "ZBE/SDL/factories/drawers/SpriteSheetSDLDrawerFtry.h"
#include "ZBE/SDL/factories/daemons/BasicPreLoopSDLDaemonFtry.h"
#include "ZBE/SDL/factories/daemons/BasicPostLoopSDLDaemonFtry.h"

#include "ZBE/SDL/events/KeyMouseEventWatcher.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the interface of a Factory.
 */
class ZBEAPI SDLFactories : public Daemon {
public:
  ~SDLFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load(){
    auto& factories = RsrcStore<Factory>::getInstance();
    factories.insert("SDLWindowFtry", std::make_shared<SDLWindowFtry>());
    factories.insert("SDLOGLWindowFtry", std::make_shared<SDLOGLWindowFtry>());
    factories.insert("SDLImgLoaderFtry", std::make_shared<SDLImgLoaderFtry>());
    factories.insert("OGLImgLoaderFtry", std::make_shared<OGLImgLoaderFtry>());
    factories.insert("SDLSysTimeFtry", std::make_shared<SDLSysTimeFtry>());
    factories.insert("SpriteSheetSDLDrawerFtry", std::make_shared<SpriteSheetSDLDrawerFtry<5, uint64_t, int64_t, double, Vector2D, Vector2D> >());

    factories.insert("BasicPreLoopSDLDaemonFtry", std::make_shared<BasicPreLoopSDLDaemonFtry>());
    factories.insert("BasicPostLoopSDLDaemonFtry", std::make_shared<BasicPostLoopSDLDaemonFtry>());

    factories.insert("KeyMouseEventWatcherFtry", std::make_shared<KeyMouseEventWatcherFtry>());
  }

};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SDLFACTORIES_H_
