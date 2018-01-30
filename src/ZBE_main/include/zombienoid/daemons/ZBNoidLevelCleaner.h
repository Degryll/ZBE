/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelCleaner.h
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid Clean each level.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEANER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEANER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "zombienoid/ZBNoid.h"

#include "zombienoid/graphics/RsrcIDDictionary.h"

namespace zombienoid {
  /** \brief Defines a daemon that Load each level.
   */
  class ZBNoidLevelCleaner : public zbe::Daemon {
    public:

      ZBNoidLevelCleaner() {}
      ~ZBNoidLevelCleaner() {}

      void run();
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEANER_H
