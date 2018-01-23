/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelClear.h
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid Load each level.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEAR_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEAR_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "zombienoid/ZBNoid.h"

#include "zombienoid/graphics/RsrcIDDictionary.h"

namespace zombienoid {
  /** \brief Defines a daemon that Load each level.
   */
  class ZBNoidLevelClear : public zbe::Daemon {
    public:

      ZBNoidLevelClear(std::shared_ptr<RsrcIDDictionary> rsrcIDDic) : rsrcIDDic(rsrcIDDic)  {}
      ~ZBNoidLevelClear() {}

      void run();

    private:
      std::shared_ptr<RsrcIDDictionary> rsrcIDDic;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELCLEAR_H
