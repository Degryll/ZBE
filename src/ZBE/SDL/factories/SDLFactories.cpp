/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLFactories.cpp
 * @since 2019-02-20
 * @date 2019-02-20
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all common factories.
 */

#include "ZBE/SDL/factories/SDLFactories.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
//#include "ZBE/core/entities/avatars/AnimatedSprite.h"

#include "ZBE/SDL/factories/system/SDLWindowFtry.h"
#include "ZBE/SDL/factories/resources/SDLImgLoaderFtry.h"
#include "ZBE/SDL/factories/system/SDLSysTimeFtry.h"
#include "ZBE/SDL/factories/drawers/SpriteSheetSDLDrawerFtry.h"

#include "ZBE/SDL/factories/daemons/BasicPreLoopSDLDaemonFtry.h"
#include "ZBE/SDL/factories/daemons/BasicPostLoopSDLDaemonFtry.h"


namespace zbe {

void SDLFactories::load() {
  auto& factories = RsrcStore<Factory>::getInstance();
  factories.insert("SDLWindowFtry", std::make_shared<SDLWindowFtry>());
  factories.insert("SDLImgLoaderFtry", std::make_shared<SDLImgLoaderFtry>());
  factories.insert("SDLSysTimeFtry", std::make_shared<SDLSysTimeFtry>());
  factories.insert("SpriteSheetSDLDrawerFtry", std::make_shared<SpriteSheetSDLDrawerFtry<5, uint64_t, int64_t, double, Vector2D, Vector2D> >());

  factories.insert("BasicPreLoopSDLDaemonFtry", std::make_shared<BasicPreLoopSDLDaemonFtry>());
  factories.insert("BasicPostLoopSDLDaemonFtry", std::make_shared<BasicPostLoopSDLDaemonFtry>());
}

}  // namespace zbe
