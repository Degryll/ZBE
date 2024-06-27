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

#include <cstdio>
#include <cstdint>
#include <nlohmann/json.hpp>

#include <SDL3/SDL.h>

#include "ZBE/SDL/events/SDLEventDispatcher.h"
#include "ZBE/SDL/events/SDLEventWatcher.h"
#include "ZBE/core/io/Input.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

namespace zbe {

class KeyMouseEventWatcherFtry;

/** \brief Dispatcher for sdl events.
 */
class KeyMouseEventWatcher : public SDLEventWatcher {
public:
  friend class KeyMouseEventWatcherFtry;

  /** \brief Empty Destructor
   */
  virtual ~KeyMouseEventWatcher() = default;

  void watch(SDL_Event event) {
    if (!tryKeyboardEvent(event)) {
      tryMouseEvent(event);
    }
  }

private:
  KeyMouseEventWatcher() : inputBuffer(), inputTextBuffer(), contextTime() {}

  void set(std::shared_ptr<InputBuffer> inputBuffer, std::shared_ptr<InputTextBuffer> inputTextBuffer, std::shared_ptr<ContextTime> contextTime) {
    this->inputBuffer = inputBuffer;
    this->inputTextBuffer = inputTextBuffer;
    this->contextTime = contextTime;
  }

  uint32_t getEquivalentToSDL(SDL_Keycode k) {return (k);}

  bool tryKeyboardEvent(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      setState(getEquivalentToSDL(event.key.keysym.sym), 1.0f, event.key.timestamp);
      return true;
    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
      setState(getEquivalentToSDL(event.key.keysym.sym), 0.0f, event.key.timestamp);
      return true;
    } else if (event.type == SDL_TEXTINPUT) {
      setTextInput(event.text.text, event.text.timestamp);
      return true;
    }
    return false;
  }

  bool tryMouseEvent(SDL_Event &event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      setMouseButtonState(event, 1.0f);
      return true;
    } else if (event.type == SDL_MOUSEBUTTONUP) {
      setMouseButtonState(event, 0.0f);
      return true;
    } else if (event.type == SDL_MOUSEWHEEL) {
      setMouseWheelState(event);
      return true;
    } else if (event.type == SDL_MOUSEMOTION) {
      setMouseCoordsState(event);
      return true;
    }
    return false;
  }

  void setState(uint32_t key, float value, uint64_t time) {
    uint64_t zbeTime = MILITOZBETU(time);
    uint64_t gameTime = zbeTime - contextTime->getLostTime();
    uint64_t storeTime = quantizeTime(gameTime) + zbe::TIME_QUANTUM;
    //TODO: Ampliar la depuración a partir de aqui. El evento lo estamos registrando.
    InputStatus is(key, value, storeTime);
    inputBuffer->insert(is);
  }

  void setTextInput(std::string text, uint64_t time) {
    uint64_t zbeTime = MILITOZBETU(time);
    uint64_t gameTime = zbeTime - contextTime->getLostTime();
    uint64_t storeTime = quantizeTime(gameTime) + zbe::TIME_QUANTUM;
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
    setState(ZBEK_MOUSE_COORD_X,event.motion.x,event.key.timestamp);
    setState(ZBEK_MOUSE_COORD_Y,event.motion.y,event.key.timestamp);
    setState(ZBEK_MOUSE_OFFSET_X,event.motion.xrel,event.key.timestamp);
    setState(ZBEK_MOUSE_OFFSET_Y,event.motion.yrel,event.key.timestamp);
  }

  std::shared_ptr<InputBuffer> inputBuffer;
  std::shared_ptr<InputTextBuffer> inputTextBuffer;
  std::shared_ptr<ContextTime> contextTime;
};

class KeyMouseEventWatcherFtry : public Factory {
public:

  /** \brief Builds a SDLWindow.
   *  \param name Name for the created SDLWindow.
   *  \param cfgId SDLWindow's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto kmew = std::shared_ptr<KeyMouseEventWatcher>(new KeyMouseEventWatcher);
    kmewRsrc.insert("KeyMouseEventWatcher."s + name, kmew);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    auto cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if(!j["window"].is_string()) {
        SysError::setError("KeyMouseEventWatcher config for window: "s + j["window"].get<std::string>() + ": must be a window name."s);
        return;
      }
      if(!j["contextTime"].is_string()) {
        SysError::setError("KeyMouseEventWatcher config for contextTime: "s + j["contextTime"].get<std::string>() + ": must be a context time name."s);
        return;
      }

      std::string windowName = j["window"].get<std::string>();
      if(!ibuffRsrc.contains("SDLOGLWindow."s + windowName + ".InputBuffer")) {
        SysError::setError("KeyMouseEventWatcher config for window: "s + windowName + ".InputBuffer does not exits."s);
        return;
      }
      if(!itBuffRsrc.contains("SDLOGLWindow."s + windowName + ".InputTextBuffer")) {
        SysError::setError("KeyMouseEventWatcher config for window: "s + windowName + ".InputTextBuffer does not exits."s);
        return;
      }
      if(!sdlEDRsrc.contains("SDLOGLWindow."s + windowName + ".SDLEventDispatcher")) {
        SysError::setError("KeyMouseEventWatcher config for window: "s + windowName + ".SDLEventDispatcher does not exits."s);
        return;
      }

      std::string contextTimeName = j["contextTime"].get<std::string>();
      if(!cTimeRsrc.contains("ContextTime."s + contextTimeName)) {
        SysError::setError("InputEventGeneratorFtry config for contextTime: "s + contextTimeName + " does not exits."s);
        return;
      }

      auto kmew = kmewRsrc.get("KeyMouseEventWatcher."s + name);
      auto ibuff = ibuffRsrc.get("SDLOGLWindow."s + windowName + ".InputBuffer");
      auto itbuff = itBuffRsrc.get("SDLOGLWindow."s + windowName + ".InputTextBuffer");
      auto ed = sdlEDRsrc.get("SDLOGLWindow."s + windowName + ".SDLEventDispatcher");
      auto cTime = cTimeRsrc.get("ContextTime."s + contextTimeName);
      kmew->set(ibuff, itbuff, cTime);
      ed->addWatcher(kmew);

    } else {
      SysError::setError("KeyMouseEventWatcherFtry config for "s + name + " not found."s);
    }

  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<KeyMouseEventWatcher> &kmewRsrc = RsrcStore<KeyMouseEventWatcher>::getInstance();
  RsrcStore<InputBuffer>& ibuffRsrc = RsrcStore<InputBuffer>::getInstance();
  RsrcStore<InputTextBuffer>& itBuffRsrc = RsrcStore<InputTextBuffer>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcStore<SDLEventDispatcher>& sdlEDRsrc = RsrcStore<SDLEventDispatcher>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_SDL_EVENTS_KEYMOUSEEVENTWATCHER_H
