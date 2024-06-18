/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleImGuiTest.h
 * @since 2018-06-13
 * @date 2018-06-13
 * @author Ludo Degryll
 * @brief
 */

#ifndef ZBE_OGL_DAEMONS_SIMPLEIMGUITEST_H
#define ZBE_OGL_DAEMONS_SIMPLEIMGUITEST_H

#include <memory>


#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/system.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/tools/graphics/Camera.h"

#include "ZBE/SDL/OGL/ImGui/SDLOGLImGuiWindow.h"

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class SimpleImGuiTest : public Daemon {
public:

  SimpleImGuiTest(std::shared_ptr<SDLOGLImGuiWindow> window) : window(window) {}

  /** \brief Destructor.
   */
  ~SimpleImGuiTest() {}

  /** \brief Do the actual Daemon job.
   */
  void run() {
    ImGui::Begin("Hello, world!");
    ImGui::Checkbox("Demo Window", &show_demo_window);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);
  }

private:
  std::shared_ptr<SDLOGLWindow> window;
  bool show_demo_window = true;
};

}  // namespace zbe

#endif  // ZBE_OGL_DAEMONS_SIMPLEIMGUITEST_H
