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
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/tools/graphics/Camera.h"
#include "ZBE/SDL/OGL/ImGui/ImGuiSDLOGLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

namespace zbe {
/** \brief
 */
class ZBEAPI ImGuiPreLoopDaemon : public Daemon {
public:

  ImGuiPreLoopDaemon(const ImGuiPreLoopDaemon&) = delete; //!< Avoid copy.
  void operator=(const ImGuiPreLoopDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */
  ImGuiPreLoopDaemon(): window(nullptr) {}

  /** \brief Builds a BasicPostLoopSDLDaemon from a window.
   *  \param window windo to use.
   */
  ImGuiPreLoopDaemon(std::shared_ptr<zbe::ImGuiSDLOGLWindow> window) : window(window) {}

  /** \brief Destroys the ImGuiPreLoopDaemon
   */
  virtual ~ImGuiPreLoopDaemon() = default;

  /** \brief Sets the window. Use with empty constructor.
   *  \param window windo to use.
   */
  void setWindow(std::shared_ptr<zbe::ImGuiSDLOGLWindow> window) {
    this->window = window;
  }

  /** \brief Runs the daemon.
   */
  void run() override {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // glViewport(0, 0, window->getDisplayX(), window->getDisplayY());
    // glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    sdled->run();
    cam->update();
}

void setProgram(std::shared_ptr<SDLOGLWindow> window, uint64_t programId) {
  gProgramID = window->getShaderStore()->getShader(programId);
}

void setCamera(std::shared_ptr<Camera> cam) {
  this->cam = cam;
}

void setSDLEventDispatcher(std::shared_ptr<SDLEventDispatcher> sdled) {
  this->sdled = sdled;
}

private:
DISABLE_DLL_WARN
  std::shared_ptr<zbe::ImGuiSDLOGLWindow> window;
  GLuint gProgramID;
  std::shared_ptr<Camera> cam;
  std::shared_ptr<SDLEventDispatcher> sdled;
DISABLE_WARNING_POP()
};

class ImGuiPreLoopDaemonFtry : virtual public Factory {
public:

  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto igpld = std::make_shared<ImGuiPreLoopDaemon>();
    daemonRsrc.insert("Daemon."s + name, igpld);
    imGuiPreLoopDaemonRsrc.insert("ImGuiPreLoopDaemon."s + name, igpld);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json window = j["window"];
      json programId = j["programId"];
      json camera = j["camera"];
      if(!window.is_string()) {
        SysError::setError("Bad config for ImGuiPreLoopDaemonFtry - window."s + window.get<std::string>());
        return;
      }
      if(!camera.is_string()) {
        SysError::setError("Bad config for ImGuiPreLoopDaemonFtry - camera."s + camera.get<std::string>());
        return;
      }
      if(!programId.is_string()) {
        SysError::setError("Bad config for ImGuiPreLoopDaemonFtry - program."s + programId.get<std::string>());
        return;
      }

      auto winname = window.get<std::string>();
      auto camname = camera.get<std::string>();
      auto pidName = programId.get<std::string>();

      auto win = imguiSdloglWindowRsrc.get("ImGuiSDLOGLWindow."s + winname);
      auto sdled = sdlEvenDWindowRsrc.get("ImGuiSDLOGLWindow."s + winname + ".SDLEventDispatcher");
      auto cam = cameraRsrc.get("Camera."s + camname);
      auto p = uintStore.get(pidName);

      auto imGuiPreLoopDaemon = imGuiPreLoopDaemonRsrc.get("ImGuiPreLoopDaemon."s + name);
      imGuiPreLoopDaemon->setProgram(win, p);
      imGuiPreLoopDaemon->setCamera(cam);
      imGuiPreLoopDaemon->setSDLEventDispatcher(sdled);
    } else {
      SysError::setError("ImGuiPreLoopDaemonFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ImGuiSDLOGLWindow> &imguiSdloglWindowRsrc = RsrcStore<ImGuiSDLOGLWindow>::getInstance();
  RsrcStore<Camera> &cameraRsrc = RsrcStore<Camera>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<ImGuiPreLoopDaemon> &imGuiPreLoopDaemonRsrc = RsrcStore<ImGuiPreLoopDaemon>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<SDLEventDispatcher> &sdlEvenDWindowRsrc = RsrcStore<SDLEventDispatcher>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IMGUIPRELOOPDAEMON_H_
