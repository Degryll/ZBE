/**
 * Copyright 2015 Batis Degryll Ludo
 * @file
 * @since 2017-05-11
 * @date 2017-05-11
 * @author Batis
 * @brief
 */

#ifndef CORE_DAEMONS_BASICPRELOOPTIMEDAEMON_H_
#define CORE_DAEMONS_BASICPRELOOPTIMEDAEMON_H_

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/core/system/SysTime.h"

namespace zbe {
  /** \brief
   */
  class BasicPreLoopTimeDaemon : public Daemon {
    public:

      BasicPreLoopTimeDaemon(const BasicPreLoopTimeDaemon&) = delete;
      void operator=(const BasicPreLoopTimeDaemon&) = delete;

      BasicPreLoopTimeDaemon(): sysTime(zbe::SysTime::getInstance()) {}

      /** \brief Destroys the BasicPreLoopTimeDaemon
       */
      virtual ~BasicPreLoopTimeDaemon() {}

      /** \brief Runs the daemon.
       */
      void run();

    private:

      zbe::SysTime &sysTime;

  };
}  // namespace zbe


#endif // CORE_DAEMONS_BASICPRELOOPTIMEDAEMON_H_
