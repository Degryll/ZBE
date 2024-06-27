/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.h
 * @since 2016-04-27
 * @date 2020-04-16
 * @author Ludo Degryll
 * @brief Dispatcher for sdl events.
 */

#ifndef ZBE_SDL_EVENTS_SDLEVENTDISPATCHER_H
#define ZBE_SDL_EVENTS_SDLEVENTDISPATCHER_H

#include <cstdint>
#include <forward_list>
#include <memory>

// #include <imgui.h>
// #include <imgui_impl_sdl.h>

#include <SDL3/SDL.h>

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/SDL/events/SDLEventWatcher.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Dispatcher for sdl events.
 */
class ZBEAPI SDLEventDispatcher {
public:
  SDLEventDispatcher(SDLEventDispatcher const&)    = delete;  //!< Needed for singleton.
  void operator=(SDLEventDispatcher const&) = delete;  //!< Needed for singleton.

  SDLEventDispatcher() : sdl(SDL_Starter::getInstance(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS)), /*inputBuffer(std::make_shared<InputBuffer>()), inputTextBuffer(std::make_shared<InputTextBuffer>()), contextTime(SysTime::getInstance()),*/ watchers() {}

  /** \brief Destructor. It will shutdown SDL subsystems.
   */
  ~SDLEventDispatcher() {
    sdl.quitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS);
  }

  /** \brief Singleton implementation.
   *  \return The only instance of the SDLEventDispatcher.
   */
  static SDLEventDispatcher& getInstance() {
    static SDLEventDispatcher instance;
    return (instance);
  }
  void addWatcher(std::shared_ptr<SDLEventWatcher> watcher) {
    // watcher->set(inputBuffer, inputTextBuffer, contextTime);
    watchers.push_front(watcher);
  }

  /** \brief Distribute SDL events in the appropriate structures of the system.
   */
  inline void run() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      for(auto& w : watchers) {
        w->watch(event);
      }
    }
  }

private:

  SDL_Starter &sdl;
  std::forward_list<std::shared_ptr<SDLEventWatcher> > watchers;
};

}  // namespace zbe

#endif  // ZBE_SDL_EVENTS_SDLEVENTDISPATCHER_H
