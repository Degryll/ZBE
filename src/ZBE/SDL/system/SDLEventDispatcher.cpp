/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.h
 * @since 2016-04-27
 * @date 2018-03-28
 * @author Ludo Batis Degryll
 * @brief Dispatcher for sdl events.
 */

#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/io/Input.h"
#include "ZBE/core/io/InputStatus.h"

namespace zbe {

SDLEventDispatcher::~SDLEventDispatcher() {
  sdl.quitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS);
}

//void SDLEventDispatcher::run() {
//  SDL_Event event;
//  while (SDL_PollEvent(&event)) {
//    ImGui_ImplSDL2_ProcessEvent(&event);
////    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
////      printf("%u -> %u\n", event.key.keysym.sym, event.key.timestamp); fflush(stdout);
////    } else {
////      printf("%d x %d -> %u\n", event.motion.x, event.motion.y, event.key.timestamp); fflush(stdout);
////    }
////    if (!tryKeyboardEvent(event)) {
////      tryMouseEvent(event);
////    }
//  }
//}

bool SDLEventDispatcher::tryKeyboardEvent(SDL_Event &event){
  if (event.type == SDL_KEYDOWN) {
//    printf("key down\n"); fflush(stdout);
    setState(getEquivalentToSDL(event.key.keysym.sym), 1.0f, event.key.timestamp);
    return true;
  } else if (event.type == SDL_KEYUP) {
//    printf("key up\n"); fflush(stdout);
    setState(getEquivalentToSDL(event.key.keysym.sym), 0.0f, event.key.timestamp);
    return true;
  } else if (event.type == SDL_TEXTINPUT) {
//    printf("text input\n"); fflush(stdout);
    setTextInput(event.text.text, event.text.timestamp);
    return true;
  }
  return false;
}

bool SDLEventDispatcher::tryMouseEvent(SDL_Event &event){
  if (event.type == SDL_MOUSEBUTTONDOWN) {
//    printf("Button down\n"); fflush(stdout);
    setMouseButtonState(event, 1.0f);
    return true;
  } else if (event.type == SDL_MOUSEBUTTONUP) {
//    printf("Button up\n"); fflush(stdout);
    setMouseButtonState(event, 0.0f);
    return true;
  } else if (event.type == SDL_MOUSEWHEEL){
//    printf("mouse wheel\n"); fflush(stdout);
    setMouseWheelState(event);
    return true;
  } else if (event.type == SDL_MOUSEMOTION){
//    printf("mouse motion\n"); fflush(stdout);
    setMouseCoordsState(event);
    return true;
  }
  return false;
}

void SDLEventDispatcher::setState(uint32_t key, float value, int64_t time) {
  int64_t zbeTime = MILITOZBETU(time);
  int64_t gameTime = zbeTime - contextTime->getLostTime();
  int64_t storeTime = quantizeTime(gameTime) + zbe::TIME_QUANTUM;
  InputStatus is(key, value, storeTime);
//  printf("insert key and mouse %llu\n", inputBuffer->size()); fflush(stdout);
  inputBuffer->insert(is);
//  printf("after %llu\n", inputBuffer->size()); fflush(stdout);
}

void SDLEventDispatcher::setTextInput(std::string text, int64_t time) {
  int64_t zbeTime = MILITOZBETU(time);
  int64_t gameTime = zbeTime - contextTime->getLostTime();
  int64_t storeTime = quantizeTime(gameTime) + zbe::TIME_QUANTUM;
  InputText it(text, storeTime);
//  printf("insert text\n"); fflush(stdout);
  inputTextBuffer->insert(it);
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
  setState(key,value,event.key.timestamp);
}

void SDLEventDispatcher::setMouseWheelState(SDL_Event &event) {
  setState(ZBEK_MOUSE_WHEEL_X,event.wheel.x,event.key.timestamp);
  setState(ZBEK_MOUSE_WHEEL_Y,event.wheel.y,event.key.timestamp);
}

void SDLEventDispatcher::setMouseCoordsState(SDL_Event &event) {
  setState(ZBEK_MOUSE_OFFSET_X,event.motion.x,event.key.timestamp);
  setState(ZBEK_MOUSE_OFFSET_Y,event.motion.y,event.key.timestamp);
}

}  // namespace zbe
