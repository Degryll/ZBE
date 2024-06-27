/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelReset.h
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief Reset the game.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELRESET_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELRESET_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBNoid.h"

#include "graphics/RsrcIDDictionary.h"

namespace zombienoid {
  /** \brief Defines a daemon that reset the game.
   */
  class ZBNoidLevelReset : public zbe::Daemon {
    public:

      ZBNoidLevelReset() {}
      ~ZBNoidLevelReset() {}

      void run() override;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELRESET_H
