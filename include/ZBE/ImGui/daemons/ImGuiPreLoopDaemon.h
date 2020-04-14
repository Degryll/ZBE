/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImGuiPreLoopDaemon.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis
 * @brief Daemon that runs before the main loop.
 * at the beginning of every frame:
 * Clears the window and captures SDL events.
 */

#ifndef ZBE_SDL_DAEMONS_IMGUIPRELOOPDAEMON_H_
#define ZBE_SDL_DAEMONS_IMGUIPRELOOPDAEMON_H_

#include <memory>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/OGL/ImGui/SDLOGLImGuiWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {
/** \brief
 */
class ImGuiPreLoopDaemon : public Daemon {
public:

  ImGuiPreLoopDaemon(const ImGuiPreLoopDaemon&) = delete; //!< Avoid copy.
  void operator=(const ImGuiPreLoopDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */
  ImGuiPreLoopDaemon(): window(nullptr) {}

  /** \brief Builds a BasicPostLoopSDLDaemon from a window.
   *  \param window windo to use.
   */
  ImGuiPreLoopDaemon(std::shared_ptr<zbe::SDLOGLImGuiWindow> window) : window(window) {}

  /** \brief Destroys the ImGuiPreLoopDaemon
   */
  virtual ~ImGuiPreLoopDaemon() {}

  /** \brief Sets the window. Use with empty constructor.
   *  \param window windo to use.
   */
  void setWindow(std::shared_ptr<zbe::SDLOGLImGuiWindow> window) {
    this->window = window;
  }

  /** \brief Runs the daemon.
   */
  void run() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window->getSDL_Window());
    ImGui::NewFrame();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glViewport(0, 0, window->getDisplayX(), window->getDisplayY());
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

private:
  std::shared_ptr<zbe::SDLOGLImGuiWindow> window;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IMGUIPRELOOPDAEMON_H_
