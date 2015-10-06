/**
 * Copyright 2015 Batis Degryll Ludo
 * @file Behavior.h
 * @since 2014-09-12
 * @date 2015-05-04
 * @author Ludo
 * @brief Define the minimal functions of demons.
 */

#ifndef CORE_DAEMONS_DAEMON_H
#define CORE_DAEMONS_DAEMON_H

namespace zbe {
  class Daemon {
    public:
      virtual void run() = 0;
      virtual ~Daemon(){};
  };
}

#endif // CORE_DAEMONS_DAEMON_H
