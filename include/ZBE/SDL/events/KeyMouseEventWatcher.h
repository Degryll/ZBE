/**
 * Copyright 2016 Batis Degryll Ludo
 * @file KeyMouseEventWatcher.h
 * @since 2020-04-16
 * @date 2020-04-16
 * @author Degryll
 * @brief Watcher that attend keyboard and mouse events.
 */

#ifndef ZBE_SDL_EVENTS_KEYMOUSEEVENTWATCHER_H
#define ZBE_SDL_EVENTS_KEYMOUSEEVENTWATCHER_H

#include <cstdint>
//#include <list>
//#include <map>
//#include <memory>

#include <SDL2/SDL.h>

#include "ZBE/SDL/events/SDLEventWatcher.h"
#include "ZBE/core/io/Input.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Dispatcher for sdl events.
 */
class KeyMouseEventWatcher : public SDLEventWatcher {
public:

  KeyMouseEventWatcher() : inputBuffer(), inputTextBuffer(), contextTime() {}

  /** \brief Empty Destructor
   */
  ~KeyMouseEventWatcher() {}

  void set(std::shared_ptr<InputBuffer> inputBuffer, std::shared_ptr<InputTextBuffer> inputTextBuffer, std::shared_ptr<ContextTime> contextTime) {
    this->inputBuffer = inputBuffer;
    this->inputTextBuffer = inputTextBuffer;
    this->contextTime = contextTime;
  }

  void watch(SDL_Event event) {
    if (!tryKeyboardEvent(event)) {
      tryMouseEvent(event);
    }
  }

private:
  uint32_t getEquivalentToSDL(SDL_Keycode k) {return (k);}

  bool tryKeyboardEvent(SDL_Event &event){
    if (event.type == SDL_KEYDOWN) {
      setState(getEquivalentToSDL(event.key.keysym.sym), 1.0f, event.key.timestamp);
      return true;
    } else if (event.type == SDL_KEYUP) {
      setState(getEquivalentToSDL(event.key.keysym.sym), 0.0f, event.key.timestamp);
      return true;
    } else if (event.type == SDL_TEXTINPUT) {
      setTextInput(event.text.text, event.text.timestamp);
      return true;
    }
    return false;
  }

  bool tryMouseEvent(SDL_Event &event){
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      setMouseButtonState(event, 1.0f);
      return true;
    } else if (event.type == SDL_MOUSEBUTTONUP) {
      setMouseButtonState(event, 0.0f);
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

  void setState(uint32_t key, float value, int64_t time) {
    int64_t zbeTime = MILITOZBETU(time);
    int64_t gameTime = zbeTime - contextTime->getLostTime();
    int64_t storeTime = quantizeTime(gameTime) + zbe::TIME_QUANTUM;
    InputStatus is(key, value, storeTime);
    inputBuffer->insert(is);
  }

  void setTextInput(std::string text, int64_t time) {
    int64_t zbeTime = MILITOZBETU(time);
    int64_t gameTime = zbeTime - contextTime->getLostTime();
    int64_t storeTime = quantizeTime(gameTime) + zbe::TIME_QUANTUM;
    InputText it(text, storeTime);
    inputTextBuffer->insert(it);
  }

  void setMouseButtonState(SDL_Event &event, float value) {
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

  void setMouseWheelState(SDL_Event &event) {
    setState(ZBEK_MOUSE_WHEEL_X,event.wheel.x,event.key.timestamp);
    setState(ZBEK_MOUSE_WHEEL_Y,event.wheel.y,event.key.timestamp);
  }

  void setMouseCoordsState(SDL_Event &event) {
    setState(ZBEK_MOUSE_OFFSET_X,event.motion.x,event.key.timestamp);
    setState(ZBEK_MOUSE_OFFSET_Y,event.motion.y,event.key.timestamp);
  }

  std::shared_ptr<InputBuffer> inputBuffer;
  std::shared_ptr<InputTextBuffer> inputTextBuffer;
  std::shared_ptr<ContextTime> contextTime;
};

}  // namespace zbe

#endif  // ZBE_SDL_EVENTS_KEYMOUSEEVENTWATCHER_H
