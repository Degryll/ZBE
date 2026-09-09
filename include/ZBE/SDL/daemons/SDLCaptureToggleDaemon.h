/**
 * Copyright 2015 Batis Degryll Ludo
 * @file IOPreLoopSDL.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis
 * @brief Daemon that runs before the main loop.
 * at the beginning of every frame:
 * Clears the window and captures SDL events.
 */

#ifndef ZBE_SDL_CAPTURETOGGLEDAEMON_H_
#define ZBE_SDL_CAPTURETOGGLEDAEMON_H_

#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

#include "ZBE/core/system/system.h"

namespace zbe {
/** \brief
 */
class ZBEAPI SDLCaptureToggleDaemon : public Daemon {
  public:

    SDLCaptureToggleDaemon(const SDLCaptureToggleDaemon&) = delete; //!< Avoid copy.
    void operator=(const SDLCaptureToggleDaemon&) = delete; //!< Avoid copy.

    /** \brief Empty constructor.
     */
    SDLCaptureToggleDaemon() {}

    /** \brief Destroys the SDLCaptureToggleDaemon
     */
    virtual ~SDLCaptureToggleDaemon() = default;

    /** \brief Runs the daemon.
     */
    void run() override {
      capture = !capture;
      SDL_CaptureMouse(capture ? SDL_FALSE : SDL_TRUE);
      SDL_SetRelativeMouseMode(capture ? SDL_FALSE : SDL_TRUE);
      // TODO esto también tiene que estár asociado al value de la entidad game.
    };
  private:
    bool capture = false;
};


class ZBEAPI ParametricSDLCaptureToggleDaemon : public Daemon {
public:
  ParametricSDLCaptureToggleDaemon() = default;

  ParametricSDLCaptureToggleDaemon(const ParametricSDLCaptureToggleDaemon&) = delete; //!< Avoid copy.
  void operator=(const ParametricSDLCaptureToggleDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */

  /** \brief Destroys the ParametricSDLCaptureToggleDaemon
   */
  virtual ~ParametricSDLCaptureToggleDaemon() = default;

  void setCapture(std::shared_ptr<Value<bool>> capture) {
    this->capture = capture;
  }

  /** \brief Runs the daemon.
   */
  void run() override {

    bool captureVal = this->capture->get();
    SDL_CaptureMouse(captureVal ? SDL_TRUE : SDL_FALSE);
    SDL_SetRelativeMouseMode(captureVal ? SDL_TRUE : SDL_FALSE);
  };


private:
DISABLE_DLL_WARN
  std::shared_ptr<Value<bool>> capture;
DISABLE_WARNING_POP()
};


class ParametricSDLCaptureToggleDaemonFtry : public Factory {
public:

  /** \brief Creates a OnceDaemon from a file.
   *  \param name Name for the created OnceDaemon.
   *  \param cfgId item's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<ParametricSDLCaptureToggleDaemon> od = std::make_shared<ParametricSDLCaptureToggleDaemon>();
    parametricSDLCaptureToggleDaemonStore.insert("ParametricSDLCaptureToggleDaemon."s + name, od);
    daemonStore.insert("Daemon."s + name, od);
  }

  /** \brief Set-up a HandlerTicketTogglerDmn.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    auto httd = parametricSDLCaptureToggleDaemonStore.get("ParametricSDLCaptureToggleDaemon."s + name);
    if(cfg) {
      auto j = *cfg;

      if (!j["entity"].is_string()) {
        SysError::setError("ParametricSDLCaptureToggleDaemon " + name + " config for entity must be a string."s);
        return;
      }
      auto entity = entityStore.get("Entity."s + j["entity"].get<std::string>());
      if (!entity) {
        SysError::setError("ParametricSDLCaptureToggleDaemon " + name + " config for entity not found."s);
        return;
      }
      if (!j["valueIdx"].is_string()) {
        SysError::setError("ParametricSDLCaptureToggleDaemon " + name + " config for valueIdx must be a string."s);
        return;
      }

      uint64_t valueIdx = uintStore.get(j["valueIdx"].get<std::string>());

      auto value = entity->getBool(valueIdx);
      if (!value) {
        SysError::setError("ParametricSDLCaptureToggleDaemon " + name + " config for valueIdx not found."s);
        return;
      }
      httd->setCapture(value);
      
    } else {
      SysError::setError("ParametricSDLCaptureToggleDaemon config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ParametricSDLCaptureToggleDaemon>& parametricSDLCaptureToggleDaemonStore = RsrcStore<ParametricSDLCaptureToggleDaemon>::getInstance();
  RsrcStore<Daemon>& daemonStore = RsrcStore<Daemon>::getInstance();
  RsrcStore<Entity>& entityStore = RsrcStore<Entity>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
};


}  // namespace zbe

#endif  // ZBE_SDL_CAPTURETOGGLEDAEMON_H_
