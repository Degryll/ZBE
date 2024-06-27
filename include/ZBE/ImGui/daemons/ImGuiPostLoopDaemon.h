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

#ifndef ZBE_SDL_DAEMONS_IMGUIPOSTLOOPDAEMON_H_
#define ZBE_SDL_DAEMONS_IMGUIPOSTLOOPDAEMON_H_

#include <memory>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/OGL/ImGui/SDLOGLImGuiWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {
/** \brief Basic post-loop daemon used for SDL
 */
class ImGuiPostLoopDaemon : public Daemon {
public:
  ImGuiPostLoopDaemon(const ImGuiPostLoopDaemon&) = delete; //!< Avoid copy.
  void operator=(const ImGuiPostLoopDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty builder.
   */
  ImGuiPostLoopDaemon(): window(nullptr) {}

  /** \brief Builds a ImGuiPostLoopDaemon from a window.
   *  \param window windo to use.
   */
  ImGuiPostLoopDaemon(std::shared_ptr<zbe::SDLOGLImGuiWindow> window): window(window) {}

  /** \brief Destroys the ImGuiPostLoopDaemon
   */
  ~ImGuiPostLoopDaemon() {}

  /** \brief Sets the the window. Use with empty constructor.
   *  \param window windo to use.
   */
  void setWindow(std::shared_ptr<zbe::SDLOGLImGuiWindow> window) {
    this->window = window;
  }

  /** \brief Runs the daemon.
   */
  void run() override {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window->getSDL_Window());
  }

private:
  std::shared_ptr<zbe::SDLOGLImGuiWindow> window;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IMGUIPOSTLOOPDAEMON_H_
