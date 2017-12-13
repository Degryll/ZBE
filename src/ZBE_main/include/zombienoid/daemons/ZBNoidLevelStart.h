/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelStart.h
 * @since 2017-08-26
 * @date 2017-08-26
 * @author Degryll Ludo Batis
 * @brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELSTART_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELSTART_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/MainLoop.h"

#include "ZBE/core/tools/shared/Value.h"


namespace zombienoid {
  /** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
   */
  class ZBNoidLevelStart : public zbe::Daemon {
    public:

      ZBNoidLevelStart(const ZBNoidLevelStart&) = delete;
      void operator=(const ZBNoidLevelStart&) = delete;

      ZBNoidLevelStart(std::shared_ptr<zbe::Value<int64_t> > nlifes, zbe::MainLoop* mainloop) : nl(nlifes), ml(mainloop) {}

      ~ZBNoidLevelStart(){}

      void run(){}

    private:
      std::shared_ptr<zbe::Value<int64_t> > nl;
      zbe::MainLoop* ml;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLEVELSTART_H
