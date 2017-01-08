/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.h
 * @since 2016-04-27
 * @date 2016-04-27
 * @author Ludo
 * @brief Dispatcher for sdl events. Implementation file.
 */

#include "ZBE/SDL/system/SDLEventDispatcher.h"

namespace zbe {

void SDLEventDispatcher::run() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (!tryKeyboardEvent(event)) {
      tryMouseEvent(event);
    }
  }
}

inline bool SDLEventDispatcher::tryKeyboardEvent(SDL_Event &event){
    if (event.type == SDL_KEYDOWN) {
      setState(getEquivalentToSDL(event.key.keysym.sym),1.0f,event.key.timestamp);
      return true;
    } else if (event.type == SDL_KEYUP) {
      setState(getEquivalentToSDL(event.key.keysym.sym),0.0f,event.key.timestamp);
      return true;
    }
    return false;
}

inline bool SDLEventDispatcher::tryMouseEvent(SDL_Event &event){
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      setMouseButtonState(event,1.0f);
      return true;
    } else if (event.type == SDL_MOUSEBUTTONUP) {
      setMouseButtonState(event,0.0f);
      return true;
    } else if (event.type == SDL_MOUSEWHEEL){
      setMouseWheelState(event);
      return true;
    } else if (event.type == SDL_MOUSEMOTION){
      setMouseCoordsState(event);
      return true;
    }
    return false;
}

inline void SDLEventDispatcher::setState(uint32_t key, float value, uint64_t time){
  InputStatus is(key,value,time);
  inputBuffer.insert(is);
}

inline void SDLEventDispatcher::setMouseWheelState(SDL_Event &event) {
  setState(ZBEK_MOUSE_WHEEL_X,event.wheel.x,event.key.timestamp);
  setState(ZBEK_MOUSE_WHEEL_Y,event.wheel.y,event.key.timestamp);
}

inline void SDLEventDispatcher::setMouseCoordsState(SDL_Event &event) {
  setState(ZBEK_MOUSE_OFFSET_X,event.motion.x,event.key.timestamp);
  setState(ZBEK_MOUSE_OFFSET_Y,event.motion.y,event.key.timestamp);
}

inline void SDLEventDispatcher::setMouseButtonState(SDL_Event &event, float value) {
  uint64_t key = 0;
  switch (event.button.button) {
    case SDL_BUTTON_LEFT:
      key = ZBEK_MOUSE_LEFT;
      break;
    case SDL_BUTTON_RIGHT:
      key = ZBEK_MOUSE_RIGHT;
      break;
    case SDL_BUTTON_MIDDLE:
      key = ZBEK_MOUSE_WHEEL;
      break;
    case SDL_BUTTON_X1:
      key = ZBEK_MOUSE_EB1;
      break;
    case SDL_BUTTON_X2:
      key = ZBEK_MOUSE_EB2;
      break;
    default:
      break;
  }
  setState(key,value,event.key.timestamp);
}

} // namespace zbe
