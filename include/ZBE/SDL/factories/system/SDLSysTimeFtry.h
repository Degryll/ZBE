/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLSysTimeFtry.h
 * @since 2019-06-19
 * @date 2019-06-19
 * @author Ludo Degryll Batis
 * @brief Configures SysTime to use and SDLTimer.
 */

#ifndef ZBE_SDL_FACTORIES_SYSTEM_SDLSYSTIMEFTRY_H_
#define ZBE_SDL_FACTORIES_SYSTEM_SDLSYSTIMEFTRY_H_

#include <string>

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/time/Timer.h"
#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"


#include "ZBE/SDL/tools/SDLTimer.h"

namespace zbe {

/** \brief Configures SysTime to use and SDLTimer.
 */
class SDLSysTimeFtry : virtual public Factory {
public:

  /** \brief Empty constructor
    */
  SDLSysTimeFtry() {}

  /** \brief Configures SysTime to use and SDLTimer.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void create(std::string name, uint64_t);

  /** \brief Configures SysTime to use and SDLTimer.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void setup(std::string, uint64_t);

private:
  RsrcStore<Timer> &timerRsrc = RsrcStore<Timer>::getInstance();
  RsrcStore<SDLTimer> &sdlTimerRsrc = RsrcStore<SDLTimer>::getInstance();
  RsrcStore<ContextTime> &contextTimeRsrc = RsrcStore<ContextTime>::getInstance();
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
};

} // namespace zbe

#endif  // ZBE_SDL_FACTORIES_SYSTEM_SDLSYSTIMEFTRY_H_
