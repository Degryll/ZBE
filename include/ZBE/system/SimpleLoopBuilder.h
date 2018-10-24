/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidMainGameBuilder.h
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid builder of the main game (the actual game, no tittle screens).
 */

#ifndef ZBE_SYSTEM_SIMPLELOOPBUILDER_H
#define ZBE_SYSTEM_SIMPLELOOPBUILDER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI SimpleEventDistpacher : public Daemon {

void run() {
  SDLEventDispatcher::getInstance().run();
}

}

/** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
 */
class ZBEAPI SimpleLoopBuilder {
public:
  SimpleLoopBuilder() {}
  ~SimpleLoopBuilder() {}

  std::shared_ptr<zbe::MainLoop> build();
};


}  // namespace zombienoid


#endif // ZBE_SYSTEM_SIMPLELOOPBUILDER_H
