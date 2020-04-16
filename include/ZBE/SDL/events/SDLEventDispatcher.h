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

#include <imgui.h>
#include <imgui_impl_sdl.h>

#include <SDL2/SDL.h>

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

  /** \brief Returns the InputBuffer where the input info will be written.
   *  \return The InputBuffer.
   */
  std::shared_ptr<InputBuffer> getInputBuffer() {return inputBuffer;}

  /** \brief Returns the InputTextBuffer where the input text info will be written.
   *  \return The InputTextBuffer.
   */
  std::shared_ptr<InputTextBuffer> getInputTextBuffer() {return inputTextBuffer;}

  void addWatcher(std::shared_ptr<SDLEventWatcher> watcher) {
    watcher->set(inputBuffer, inputTextBuffer, contextTime);
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
      //ImGui_ImplSDL2_ProcessEvent(&event);
//      if (!tryKeyboardEvent(event)) {
//        tryMouseEvent(event);
//      }
    }
  }

private:
  SDLEventDispatcher() : sdl(SDL_Starter::getInstance(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS)), inputBuffer(std::make_shared<InputBuffer>()), inputTextBuffer(std::make_shared<InputTextBuffer>()), contextTime(SysTime::getInstance()), watchers() {}

//  bool tryKeyboardEvent(SDL_Event &event);
//
//  bool tryMouseEvent(SDL_Event &event);
//
//  void setState(uint32_t key, float value, int64_t time);
//
//  void setTextInput(std::string text, int64_t time);
//
//  void setMouseButtonState(SDL_Event &event, float value);
//
//  void setMouseWheelState(SDL_Event &event);
//
//  void setMouseCoordsState(SDL_Event &event);
//
//  uint32_t getEquivalentToSDL(SDL_Keycode k) {return (k);}

  SDL_Starter &sdl;
  std::shared_ptr<InputBuffer> inputBuffer;
  std::shared_ptr<InputTextBuffer> inputTextBuffer;
  std::shared_ptr<ContextTime> contextTime;
  std::forward_list<std::shared_ptr<SDLEventWatcher> > watchers;
};

}  // namespace zbe

#endif  // ZBE_SDL_EVENTS_SDLEVENTDISPATCHER_H
