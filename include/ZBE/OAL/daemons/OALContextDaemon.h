/**
 * Copyright 2015 Batis Degryll Ludo
 * @file OALContextDaemon.h
 * @since 2019-03-19
 * @date 2019-03-19
 * @author Ludo
 * @brief Daemon that generates an OpenAL context.
 */

#ifndef ZBE_OAL_DAEMONS_OALCONTEXTDAEMON_H_
#define ZBE_OAL_DAEMONS_OALCONTEXTDAEMON_H_

#include <stdio.h>
#include <string.h>
#include <string>

#include <AL/al.h>
#include <AL/alc.h>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/OAL/tools/OALUtils.h"

//#include "ZBE/OAL/system/OALAudioStore.h"

namespace zbe {
  /** \brief Daemon that generates an OpenAL context.
   */
class ZBEAPI OALContextDaemon : public Daemon {
public:

  OALContextDaemon(const OALContextDaemon&) = delete; //!< Avoid copy.
  void operator=(const OALContextDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */
  OALContextDaemon() {}

  void run() override;
private:
  static ALCchar* getLastAudioDevice(const ALCchar *devices);

};

}  // namespace zbe

#endif  // ZBE_OAL_DAEMONS_OALCONTEXTDAEMON_H_
