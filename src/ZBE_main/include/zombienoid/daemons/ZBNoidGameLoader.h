/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelLoader.h
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid Load base game.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDGAMELOADER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDGAMELOADER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "zombienoid/ZBNoid.h"

#include "zombienoid/graphics/RsrcIDDictionary.h"

namespace zombienoid {
  /** \brief Defines a daemon that Load base game.
   */
  class ZBNoidGameLoader : public zbe::Daemon {
    public:

      ZBNoidGameLoader(std::shared_ptr<RsrcIDDictionary> rsrcIDDic) : rsrcIDDic(rsrcIDDic)  {}

      ~ZBNoidGameLoader() {}

      void run();

    private:
      std::shared_ptr<RsrcIDDictionary> rsrcIDDic;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDGAMELOADER_H
