/**
 * Copyright 2015 Batis Degryll Ludo
 * @file VoidDaemon.h
 * @since 2019-07-31
 * @date 2018-07-31
 * @author Ludo Degryll Batis
 * @brief A Daemon that does nothing.
 */

#ifndef ZBE_CORE_DAEMONS_VOIDDAEMON_H
#define ZBE_CORE_DAEMONS_VOIDDAEMON_H


#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

/** \brief Daemon that does nothing.
 */
class ZBEAPI VoidDaemon : public Daemon {
public:

  /** \brief Do nothing.
   */
  void run() {}
};

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_VOIDDAEMON_H
