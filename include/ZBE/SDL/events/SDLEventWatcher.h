/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLEventWatcher.h
 * @since 2020-04-16
 * @date 2020-04-16
 * @author Degryll
 * @brief Event watcher to be used in an event dispatcher.
 */

#ifndef ZBE_SDL_EVENTS_SDLEVENTWATCHER_H
#define ZBE_SDL_EVENTS_SDLEVENTWATCHER_H

#include <cstdint>

#include "ZBE/core/system/system.h"

#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"
#include "ZBE/core/system/SysTime.h"

namespace zbe {

/** \brief Represents a basic event. An event its something that, when it occurs, can cause some element of the game to change its state.
 */
class SDLEventWatcher {
public:

  virtual ~SDLEventWatcher() = default;  //!< Empty destructor

  /** \brief React to the Event received.
   */
  virtual void watch(SDL_Event) = 0;
};

}  // namespace zbe

#endif  // ZBE_SDL_EVENTS_SDLEVENTWATCHER_H
