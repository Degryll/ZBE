/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.h
 * @since 2016-04-27
 * @date 2016-05-13
 * @author Ludo
 * @brief Dispatcher for sdl events.
 */

#ifndef ZBE_SDL_SYSTEM_SDLEVENTDISPATCHER_H
#define ZBE_SDL_SYSTEM_SDLEVENTDISPATCHER_H

#include <memory>
#include <map>
#include <list>

#include <SDL2/SDL.h>

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/core/io/Input.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/system/SysTime.h"

namespace zbe {

/** \brief Dispatcher for sdl events.
 */
class SDLEventDispatcher {
public:
  SDLEventDispatcher(SDLEventDispatcher const&)    = delete;  //!< Needed for singleton.
  void operator=(SDLEventDispatcher const&) = delete;  //!< Needed for singleton.

  /** \brief Destructor. It will shutdown SDL subsystems.
   */
  ~SDLEventDispatcher();

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

  /** \brief Distribute SDL events in the appropriate structures of the system.
   */
  void run();

private:
  SDLEventDispatcher() : sdl(SDL_Starter::getInstance(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS)), inputBuffer(std::make_shared<InputBuffer>()), st(SysTime::getInstance()) {}

  bool tryKeyboardEvent(SDL_Event &event);

  bool tryMouseEvent(SDL_Event &event);

  void setState(uint32_t key, float value, int64_t time);

  void setMouseButtonState(SDL_Event &event, float value);

  void setMouseWheelState(SDL_Event &event);

  void setMouseCoordsState(SDL_Event &event);

  uint32_t getEquivalentToSDL(SDL_Keycode k) {return (k);}

  SDL_Starter &sdl;
  std::shared_ptr<InputBuffer> inputBuffer;
  SysTime& st;
};

}  // namespace zbe

#endif // ZBE_SDL_SYSTEM_SDLEVENTDISPATCHER_H
