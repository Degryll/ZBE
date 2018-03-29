/**
 * Copyright 2015 Batis Degryll Ludo
 * @file
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis Ludo Degryll
 * @brief Basic daemon to use in pre-loop.
 */

#ifndef ZBE_CORE_DAEMONS_BASICPRELOOPTIMEDAEMON_H_
#define ZBE_CORE_DAEMONS_BASICPRELOOPTIMEDAEMON_H_

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/core/system/SysTime.h"

namespace zbe {
/** \brief Basic daemon to use in pre-loop.
 */
class BasicPreLoopTimeDaemon : public Daemon {
public:

  BasicPreLoopTimeDaemon(const BasicPreLoopTimeDaemon&) = delete; //!< Avoid copy.
  void operator=(const BasicPreLoopTimeDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */
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

#endif  // ZBE_CORE_DAEMONS_BASICPRELOOPTIMEDAEMON_H_
