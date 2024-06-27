/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelLoader.h
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid Load each level.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELLOADER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELLOADER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBNoid.h"

#include "graphics/RsrcIDDictionary.h"

#include "ZBE/SDL/system/SDLWindow.h"

namespace zombienoid {
  /** \brief Defines a daemon that Load each level.
   */
  class ZBNoidLevelLoader : public zbe::Daemon {
    public:

      ZBNoidLevelLoader(std::shared_ptr<RsrcIDDictionary> rsrcIDDic) : rsrcIDDic(rsrcIDDic)  {}

      ~ZBNoidLevelLoader() {}

      void run() override;

    private:
      std::shared_ptr<RsrcIDDictionary> rsrcIDDic;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELLOADER_H
