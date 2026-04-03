/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImGuiPostLoopDaemon.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Daemon that runs after the main loop.
 * at the end of every frame:
 * Shows the window (if double buffer changes it).
 */

#ifndef ZBE_SDL_DAEMONS_IMGUITESTDRAWDAEMON_H_
#define ZBE_SDL_DAEMONS_IMGUITESTDRAWDAEMON_H_

#include <memory>

#include <imgui.h>
#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

class ZBEAPI ImGuiTestDrawDaemon : public Daemon {
public:
  ImGuiTestDrawDaemon(const ImGuiTestDrawDaemon&) = delete; //!< Avoid copy.
  void operator=(const ImGuiTestDrawDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty builder.
   */
  ImGuiTestDrawDaemon() {}

  /** \brief Destroys the ImGuiTestDrawDaemon
   */
  ~ImGuiTestDrawDaemon() = default;

  /** \brief Runs the daemon.
   */
  void run() override {
    ImGui::ShowDemoWindow(&show_demo_window);
    // TODO:
    // Crear una ventana que muestre info del juego (Tamaños de listas, demonios, blah blah)
    // Hay poder alternar entre que SDL caputre el ratón para manjear la cámara o no, y mostrar el cursor o no.
    // SDL_CaptureMouse(????);
    // SDL_SetRelativeMouseMode(????);
    // El título de la ventana sigue emputecido.
  }

private:
  bool show_demo_window = true;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IMGUITESTDRAWDAEMON_H_
