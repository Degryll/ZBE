/**
 * Copyright 2015 Batis Degryll Ludo
 * @file Daemon.h
 * @since 2015-05-04
 * @date 2015-12-09
 * @author Ludo
 * @brief Define the minimal functions of demons.
 */

#ifndef CORE_DAEMONS_DAEMON_H
#define CORE_DAEMONS_DAEMON_H

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
}

#endif // CORE_DAEMONS_DAEMON_H
