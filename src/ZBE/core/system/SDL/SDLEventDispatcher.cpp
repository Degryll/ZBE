/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.h
 * @since 2016-04-27
 * @date 2016-04-27
 * @author Ludo
 * @brief Dispatcher for sdl events. Implementation file.
 */

#include "ZBE/core/system/SDL/SDLEventDispatcher.h"

namespace zbe {

SDLEventDispatcher::SDLEventDispatcher():irinstance(0), changedIds(0), states(0){
    irinstance = SDLInputReader::getInstance();

    changedIds = new std::list<uint32_t>();
    states = new std::map<uint32_t, float>();
}

SDLEventDispatcher::~SDLEventDispatcher() {
  delete changedIds;
  delete states;
}

void SDLEventDispatcher::run() {
  states->clear();
  changedIds->clear();
  SDL_Event event;
  //Keyboard
  while (SDL_PollEvent(&event)) {
    if (tryKeyboardEvent(event)) {
    } else if(tryMouseEvent(event)){
    }
  }
  irinstance->setInputStatus(changedIds, states);
}

bool SDLEventDispatcher::tryKeyboardEvent(SDL_Event &event){
    if (event.type == SDL_KEYDOWN) {
      setState(getEquivalentToSDL(event.key.keysym.sym),1.0f);
      return true;
    } else if (event.type == SDL_KEYUP) {
      setState(getEquivalentToSDL(event.key.keysym.sym),0.0f);
      return true;
    }
    return false;
}

bool SDLEventDispatcher::tryMouseEvent(SDL_Event &event){
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

uint32_t SDLEventDispatcher::getEquivalentToSDL(SDL_Keycode k) {
  return k;
}

void SDLEventDispatcher::setState(uint32_t key, float value){
  (*states)[key] = value;
  changedIds->push_back(key);
}

void SDLEventDispatcher::setMouseWheelState(SDL_Event &event) {
  setState(ZBEK_MOUSE_WHEEL_X,event.wheel.x);
  setState(ZBEK_MOUSE_WHEEL_Y,event.wheel.y);
}

void SDLEventDispatcher::setMouseCoordsState(SDL_Event &event) {
  setState(ZBEK_MOUSE_OFFSET_X,event.motion.x);
  setState(ZBEK_MOUSE_OFFSET_Y,event.motion.y);
}

void SDLEventDispatcher::setMouseButtonState(SDL_Event &event, float value) {
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
  setState(key,value);
}

} // namespace zbe
