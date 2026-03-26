/**
 * Copyright 2026 Batis Degryll Ludo
 * @file SLINTSDLEventDistpatcher.h
 * @since 2026-02-19
 * @date 2026-02-19
 * @author Ludo Degryll Batis
 * @brief Dispatcher for sdl events supporting SLINT.
 */

#ifndef ZBE_SLINT_EVENTS_SLINTSDLEVENTDISTPATCHER_H
#define ZBE_SLINT_EVENTS_SLINTSDLEVENTDISTPATCHER_H

#include <cstdint>
#include <forward_list>
#include <memory>

#include "ZBE/SDL/events/SDLEventDispatcher.h"

namespace zbe {

/** \brief Dispatcher for sdl events.
 */
class ZBEAPI SLINTSDLEventDispatcher : public SDLEventDispatcher {
public:

  virtual inline void run() override {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      for(auto& w : watchers) {
        w->watch(event);
      }
      slint::platform::update_timers();
      slint::platform::dispatch_event(event);
    }
  }
};

// TODO factorias.
// Pintador ... post draw...

}  // namespace zbe

#endif  // ZBE_SLINT_EVENTS_SLINTSDLEVENTDISTPATCHER_H
