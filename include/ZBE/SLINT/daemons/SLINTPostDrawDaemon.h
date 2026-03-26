/**
 * Copyright 2025 Batis Degryll Ludo
 * @file SLINTPostLoopDaemon.h
 * @since 2026-04-05
 * @author Batis Degryll Ludo
 * @brief Post loop daemon for Slint. It should be used after the main loop, to render the Slint UI.
 */

#ifndef ZBE_SLINT_DAEMONS_SLINTPOSTDRAWDAEMON_H_
#define ZBE_SLINT_DAEMONS_SLINTPOSTDRAWDAEMON_H_

#include <memory>
#include <optional>


#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/system.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SLINT/SLINTSDLOGLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {
class ZBEAPI SLINTPostDrawDaemon : public Daemon {
public:
  SLINTPostDrawDaemon(const SLINTPostDrawDaemon&) = delete; //!< Avoid copy.
  void operator=(const SLINTPostDrawDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty builder.
   */
  SLINTPostDrawDaemon(): window(nullptr), ui(std::nullopt) {}

  /** \brief Builds a SLINTPostDrawDaemon from a window.
   *  \param window windo to use.
   */
  SLINTPostDrawDaemon(std::shared_ptr<zbe::SLINTSDLOGLWindow> window): window(window), ui(std::nullopt) {}

  /** \brief Destroys the SLINTPostDrawDaemon
   */
  ~SLINTPostDrawDaemon() = default;

  /** \brief Sets the the window. Use with empty constructor.
   *  \param window windo to use.
   */
  void setWindow(std::shared_ptr<zbe::SLINTSDLOGLWindow> window) {
    //this->window = window;
    ui = window->getUI();
  }

  /** \brief Runs the daemon.
   */
  void run() override {
    if (ui) {
      // (*ui)->run();
      slint::platform::update_timers_and_animations();
      slint::platform::render();
    }
  }

// https://chatgpt.com/share/69b33623-bb4c-800f-86f3-21c754f0dde1
// TODO: tenemos que hacer un bucle como este:

// auto ui = MainWindow::create();

// bool running = true;

// while (running) {

//     SDL_Event event;
//     while (SDL_PollEvent(&event)) {

//         if (event.type == SDL_QUIT)
//             running = false;

//         // aquí deberías reenviar eventos a Slint
//     }

//     // actualizar animaciones Slint
//     slint::platform::update_timers_and_animations();

//     // ---- render 3D ----
//     render_scene();

//     // ---- render Slint ----
//     slint::platform::render();

//     SDL_GL_SwapWindow(window);
// }

// Esto va a implicar:
// Dos demonios separados:
// Uno para slint::platform::update_timers_and_animations();
// Otro para slint::platform::render();
// Habrá que intercalarlos entre los actuales (Revisar masterDrawDaemon y postDrawDaemon)

private:
  std::shared_ptr<zbe::SLINTSDLOGLWindow> window;
  std::optional<slint::ComponentHandle<SlintUi>> ui;
};

class SLINTPostDrawDaemonFtry : virtual public Factory {
public:
  /** \brief Builds a SLINTPostDraw.
   *  \param name Name for the created SLINTPostDraw.
   *  \param cfgId SLINTPostDraw's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto slintPostDraw = std::make_shared<SLINTPostDrawDaemon>();
    daemonRsrc.insert("Daemon."s + name, slintPostDraw);
    slintPostDrawRsrc.insert("SLINTPostDrawDaemon."s + name, slintPostDraw);
  }


  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json window = j["window"];
      if(!window.is_string()) {
        SysError::setError("Bad config for SLINTPostDrawFtry - window."s + window.get<std::string>());
        return;
      }

      auto winname = j["window"].get<std::string>();
      auto win = sdloglWindowRsrc.get("SLINTSDLOGLWindow."s + winname);

      auto slintPostDraw = slintPostDrawRsrc.get("SLINTPostDrawDaemon."s + name);
      slintPostDraw->setWindow(win);
    } else {
      SysError::setError("SLINTPostDrawFtry config for "s + name + " not found."s);
    }
  }
private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SLINTSDLOGLWindow> &sdloglWindowRsrc = RsrcStore<SLINTSDLOGLWindow>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<SLINTPostDrawDaemon> &slintPostDrawRsrc = RsrcStore<SLINTPostDrawDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SLINT_DAEMONS_SLINTPOSTDRAWDAEMON_H_
