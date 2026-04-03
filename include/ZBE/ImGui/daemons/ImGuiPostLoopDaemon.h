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
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include "ZBE/SDL/sdl_warning_suppressor.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/OGL/ImGui/ImGuiSDLOGLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {
/** \brief Basic post-loop daemon used for SDL
 */
class ZBEAPI ImGuiPostLoopDaemon : public Daemon {
public:
  ImGuiPostLoopDaemon(const ImGuiPostLoopDaemon&) = delete; //!< Avoid copy.
  void operator=(const ImGuiPostLoopDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty builder.
   */
  ImGuiPostLoopDaemon(): window(nullptr) {}

  /** \brief Builds a ImGuiPostLoopDaemon from a window.
   *  \param window windo to use.
   */
  ImGuiPostLoopDaemon(std::shared_ptr<zbe::ImGuiSDLOGLWindow> window): window(window) {}

  /** \brief Destroys the ImGuiPostLoopDaemon
   */
  ~ImGuiPostLoopDaemon() = default;

  /** \brief Sets the the window. Use with empty constructor.
   *  \param window windo to use.
   */
  void setWindow(std::shared_ptr<zbe::ImGuiSDLOGLWindow> window) {
    this->window = window;
  }

  /** \brief Runs the daemon.
   */
  void run() override {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    window->glSwap();
  }

private:
  std::shared_ptr<zbe::ImGuiSDLOGLWindow> window;
};

class ZBEAPI ImGuiPostLoopDaemonFtry : public Factory {
  public:

  /** \brief Builds a SDLWindow.
   *  \param name Name for the created SDLWindow.
   *  \param cfgId SDLWindow's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    auto dmn = std::make_shared<ImGuiPostLoopDaemon>();
    mainRsrc.insert("Daemon."s + name, dmn);
    specificRsrc.insert("ImGuiPostLoopDaemon."s + name, dmn);
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
      auto igpld = specificRsrc.get("ImGuiPostLoopDaemon."s + name);
      json window = j["window"];
      if(!window.is_string()) {
        SysError::setError("Bad config for ImGuiPostLoopDaemonFtry - window."s + window.get<std::string>());
        return;
      }

      auto winname = j["window"].get<std::string>();
      auto win = imguiSdloglWindowRsrc.get("ImGuiSDLOGLWindow."s + winname);

      igpld->setWindow(win);
    } else {
      SysError::setError("ImGuiSDLOGLWindowFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ImGuiPostLoopDaemon> &specificRsrc = RsrcStore<ImGuiPostLoopDaemon>::getInstance();
  RsrcStore<Daemon> &mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ImGuiSDLOGLWindow> &imguiSdloglWindowRsrc = RsrcStore<ImGuiSDLOGLWindow>::getInstance();
};

}  // namespace zbe



#endif  // ZBE_SDL_DAEMONS_IMGUIPOSTLOOPDAEMON_H_
