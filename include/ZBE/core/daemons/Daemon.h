/**
 * Copyright 2015 Batis Degryll Ludo
 * @file Daemon.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Ludo Degryll Batis
 * @brief Define the minimal functions of demons.
 */

#ifndef ZBE_CORE_DAEMONS_DAEMON_H
#define ZBE_CORE_DAEMONS_DAEMON_H

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class Daemon {
public:

  /** \brief Do the actual Daemon job.
   */
  virtual void run() = 0;

  /** \brief Destructor.
   */
  virtual ~Daemon(){};
};

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_DAEMON_H
